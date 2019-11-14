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


	blocUse = (taille / BLOCSIZE);
	rest = taille % BLOCSIZE;
	if (rest) {
		blocUse++;
	}

	if ((freeblocks < blocUse)) {
		fprintf(stderr, "ERROR NO PLACE LEFT\n");
		return EXIT_FAILURE;
	}
	else if (!objectNotExist(nom)) {
		fprintf(stderr, "OBJECT ALREADY EXIST\n");
		return EXIT_FAILURE;
	}
	newObject = malloc(sizeof(struct objet));
	if (rest) {
		blocUse--;
	}

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

	indexFat = nextFatFreeIndex(0);
	newObject->index = indexFat;


	for (indexWriteBloc = 0; indexWriteBloc < blocUse; indexWriteBloc++) {
		writeBloc(indexFat, data, BLOCSIZE, indexWriteBloc);
		if (indexWriteBloc == blocUse - 1 && !rest) {
			FAT[indexFat] = END;
		}
		else {
			FAT[indexFat] = nextFatFreeIndex(indexFat + 1);
		}
		indexFat = FAT[indexFat];

	}

	if (rest) {
		writeBloc(indexFat, data, rest, indexWriteBloc);
		FAT[indexFat] = END;
	}

	return EXIT_SUCCESS;
}

unsigned int nextFatFreeIndex (unsigned int currentFatIndex) {

	unsigned int index = currentFatIndex;
	if (currentFatIndex < 0 || currentFatIndex >= BLOCNUM) {
		return -1;
	}
	while (index < BLOCNUM && FAT[index] != FREE) {
		index++;
	}
	return index;
}

int writeBloc (unsigned int fatIndex, const char *fullData, unsigned int dataSize, unsigned int packetNumber) {

	unsigned int index;
	char tempByte;

	if (dataSize > BLOCSIZE) {
		return EXIT_FAILURE;
	}

	for (index = 0; index < dataSize; index++) {
		tempByte = fullData[packetNumber * BLOCSIZE + index];
		volume[fatIndex * BLOCSIZE + index] = tempByte;
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
		nbBlock = (objetToDel->taille / BLOCSIZE) + 1;
		freeblocks = freeblocks + nbBlock;
		indexTemp = obj->index;
	}
	for (k = 0; k < (nbBlock); ++k) {
		if (indexTemp != END) {
			for (l = BLOCSIZE * indexTemp; l < (BLOCSIZE * (indexTemp + 1)); l++) {
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
		nbBlock = (currentObjet->taille / BLOCSIZE) + 1;


		indexTemp = currentObjet->index;
		if (strcmp(currentObjet->nom, "first")) {
			for (k = 0; k < (nbBlock); ++k) {
				if (indexTemp != END) {
					for (l = BLOCSIZE * indexTemp; l < (BLOCSIZE * indexTemp + BLOCSIZE); l++) {
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
	unsigned int numberBloc;
	unsigned int rest;

	size = objectTR->taille;

	numberBloc = size / BLOCSIZE;
	rest = size % BLOCSIZE;

	*dataOut = malloc(size);

	if (*dataOut == NULL) {
		fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		free(*dataOut);
		exit(EXIT_FAILURE);
	}
	indexFat = objectTR->index;

	for (index = 0; index < numberBloc; index++) {
		readBloc(indexFat, BLOCSIZE, *dataOut, index);
		indexFat = FAT[indexFat];
	}
	if (rest) {
		readBloc(indexFat, rest, *dataOut, index);
	}


	return EXIT_SUCCESS;
}

int readBloc (unsigned int indexFat, unsigned int size, char *str, unsigned int numberPacket) {

	unsigned int index;
	if (size > BLOCSIZE) {
		fprintf(stderr, "ERROR TO MANY DATA ASK\n");
		return EXIT_FAILURE;
	}
	for (index = 0; index < size; index++) {
		str[BLOCSIZE * numberPacket + index] = volume[BLOCSIZE * indexFat + index];
	}
	return EXIT_SUCCESS;
}

