#include <stdio.h>

#include "fat.h"
#include  <string.h>


/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/

typedef struct object object;

struct objet *obj;

char volume[BLOCSIZE * BLOCNUM];

unsigned short FAT[BLOCNUM];

unsigned short freeblocks;

struct objet *new_object () {

	struct objet *objTemp;
	objTemp = malloc(sizeof(*objTemp));

	if (objTemp == NULL) {
		fprintf(stderr, "ERROR ALLOCATION MEMORY\n");
		free(objTemp);
		exit(EXIT_FAILURE);
	}
	return objTemp;
}

void initialise_fat () {

	int index;
	struct objet *objTemp;

	for (index = 0; index < BLOCNUM; index++) {
		FAT[index] = 0xFFFF;
	}

	freeblocks = BLOCNUM;
	objTemp = new_object();
	strcpy(objTemp->nom, "first");
	objTemp->taille = 0;
	objTemp->auteur = 0;
	objTemp->index = 0;
	objTemp->next = NULL;

	obj = objTemp;

}

struct objet *rechercher_objet (char *nom) {

	struct objet *objTemp;
	objTemp = obj;

	while (objTemp != NULL) {
		if (strcmp(objTemp->nom, nom) == 0) {
			return objTemp;
		}
		objTemp = objTemp->next;
	}
	fprintf(stderr, "NO OBJECT FUND\n");
	return NULL;
}

int objectNotExist (char *nom) {

	struct objet *objTemp;
	objTemp = obj;

	while (objTemp != NULL) {
		if (!strcmp(objTemp->nom, nom)) {
			return 0;
		}
		objTemp = objTemp->next;
	}

	return 1;
}

int addNewObject (char *nom, unsigned short auteur, unsigned int taille, char *data) {

	struct objet *newObject;
	unsigned int blocUse;
	unsigned rest;
	unsigned int indexFat;
	unsigned int indexWriteBloc;

	blocUse = (taille / 512) + 1;
	if (!(freeblocks >= blocUse)) {
		fprintf(stderr, "ERROR NO PLACE LEFT\n");
		return EXIT_FAILURE;
	}
	else if (!objectNotExist(nom)) {
		fprintf(stderr, "OBJECT ALREADY EXIST\n");
		return EXIT_FAILURE;
	}
	newObject = malloc(sizeof(struct objet));

	if (newObject == NULL) {
		fprintf(stderr, "ALLOCATION MEMORY ERROR\n");
		free(newObject);
		exit(EXIT_FAILURE);
	}

	newObject->taille = taille;
	newObject->auteur = auteur;
	strcpy(newObject->nom, nom);
	newObject->next = NULL;
	insertObject(obj, newObject);

	rest = taille % 512;
	indexFat = 0;

	while (indexFat < BLOCNUM && FAT[indexFat] != FREE)
		indexFat++;
	newObject->index = indexFat;


	for (indexWriteBloc = 0; indexWriteBloc < blocUse - 1; indexWriteBloc++) {
		writeBloc(indexFat, data, 512, indexWriteBloc);
		indexFat++;
	}

	writeBloc(indexFat, data, rest, indexWriteBloc);

	return EXIT_SUCCESS;
}

int writeBloc (unsigned int fatIndex, const char *fullData, unsigned int dataSize, unsigned int packetNumber) {

	int index;
	char tempByte;

	if (dataSize > 512) {
		return EXIT_FAILURE;
	}

	FAT[fatIndex] = END;
	for (index = packetNumber * 512; index < packetNumber * 512 + dataSize; index++) {
		tempByte = fullData[index];
		volume[fatIndex * 512 + index] = tempByte;
	}
	freeblocks--;
	return EXIT_SUCCESS;
}

void insertObject (struct objet *header, struct objet *newObjet) {

	struct objet *objetTemp;
	objetTemp = header;
	while (objetTemp->next != NULL) {
		objetTemp = objetTemp->next;
	}
	objetTemp->next = newObjet;
}


int supprimer_objet (char *nom) {

	struct objet *objetToDel;
	struct objet *objectPrevious;
	int indexObjToDel;
	unsigned int nbBlock;

	unsigned short indexTemp;
	unsigned short lastIndexTemp;

	unsigned int k, l;

	objetToDel = obj;
	objectPrevious = obj;
	indexObjToDel = 0;

	if (!objectNotExist(nom) && strcmp(nom, "first")) {
		while (objetToDel != NULL) {
			indexObjToDel++;
			if (!strcmp(objetToDel->nom, nom)) {
				break;
			}
			objetToDel = objetToDel->next;
		}
	}
	else {
		fprintf(stderr, "\"%s\" CANNOT BE DELETED : NOT EXIST OR FIRST\n", nom);
	}

	if (objetToDel == NULL) {
		nbBlock = 1;
		freeblocks = freeblocks + nbBlock;
		indexTemp = 0;

	}
	else {
		nbBlock = (objetToDel->taille / 512) + 1;
		freeblocks = freeblocks + nbBlock;
		indexTemp = obj->index;
	}
	for (k = 0; k < (nbBlock); ++k) {
		if (indexTemp != END) {
			for (l = 512 * indexTemp; l < (512 * (indexTemp + 1)); l++) {
				volume[l] = 0;
			}
			lastIndexTemp = indexTemp;
			indexTemp = FAT[indexTemp];
		}
		FAT[lastIndexTemp] = FREE;
	}

	for (k = 0; k < (indexObjToDel - 2); ++k) {
		objectPrevious = objectPrevious->next;
	}
	if (objetToDel == NULL) {
		objectPrevious->next = NULL;
	}
	else {
		objectPrevious->next = objetToDel->next;
	}
	free(objetToDel);
	return EXIT_SUCCESS;
}

void printObject (struct objet *obj) {

	printf("\n");
	if (obj == NULL) {
		printf("OBJECT SECIFIED NULL\n");
	}
	else {
		printf("nom : %s \n", obj->nom);
		printf("taille : %u \n", obj->taille);
		printf("auteur : %u \n", obj->auteur);
		printf("index : %u \n", obj->index);
	}
}

void supprimer_tout () {

	struct objet *objetToDelete;
	struct objet *currentObjet;
	unsigned int nbBlock;
	unsigned short lastIndexTemp;
	unsigned short indexTemp;
	int k;
	int l;
	currentObjet = obj;
	while (currentObjet != NULL) {
		nbBlock = (currentObjet->taille / 512) + 1;


		indexTemp = currentObjet->index;
		if (strcmp(currentObjet->nom, "first")) {
			for (k = 0; k < (nbBlock); ++k) {
				if (indexTemp != END) {
					for (l = 512 * indexTemp; l < (512 * indexTemp + 512); l++) {
						volume[l] = 0;
					}
					lastIndexTemp = indexTemp;
					indexTemp = FAT[indexTemp];
				}
				FAT[lastIndexTemp] = FREE;
			}
			freeblocks = freeblocks + nbBlock;
		}

		objetToDelete = currentObjet;
		currentObjet = currentObjet->next;
		free(objetToDelete);
	}

}

int readObject (struct objet *objectTR, char **dataOut) {

	unsigned int size;
	unsigned int indexFat;
	unsigned int index;

	size = objectTR->taille;

	*dataOut = malloc(size);

	if (*dataOut == NULL) {
		fprintf(stderr, "error malloc");
		free(*dataOut);
		exit(EXIT_FAILURE);
	}
	indexFat = objectTR->index;

	for (index = 0; index < size; index++) {
		(*dataOut)[index] = volume[512 * indexFat + index];
	}
	return EXIT_SUCCESS;
}
