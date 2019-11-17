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

int creer_objet (char *nom, unsigned short auteur, unsigned int taille, char *data) {

	struct objet *newObject;
	unsigned int blocUse;
	unsigned rest;
	unsigned int indexFat;
	unsigned int indexWriteBloc;
	//unsigned int taille = size ;


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

	struct objet **objectsList;
	unsigned int nbBlock;

	objectsList = getObjects(nom);
	if (objectsList[0] == NULL || objectsList[1] == NULL) {
		return EXIT_FAILURE;
	}

	objectsList[0]->next = objectsList[1]->next;

	nbBlock = (objectsList[1]->taille) / BLOCSIZE + ((objectsList[1]->taille) % BLOCSIZE == 0 ? 0 : 1);

	freeFat(objectsList[1]->index);

	freeblocks += nbBlock;

	free(objectsList[1]);

	return EXIT_SUCCESS;




}

void freeFat (unsigned int firstIndex) {

	unsigned int indexFat = firstIndex;

	while(FAT[indexFat] != END)
	{
		FAT[indexFat] = FREE;
		indexFat++;
	}
	FAT[indexFat] = FREE;
}

struct objet **getObjects (char *name) {

	static struct objet *objectL[2];
	struct objet *objectToDel;
	struct objet *previousObject;

	objectToDel = obj;
	previousObject = NULL;
	if (!objectNotExist(name) && strcmp(name, "first")) {
		while (objectToDel != NULL) {
			if (!strcmp(objectToDel->nom, name)) {
				break;
			}
			previousObject = objectToDel;
			objectToDel = objectToDel->next;
		}
	}
	else {
		objectToDel = NULL;
		fprintf(stderr, "\"%s\" CANNOT BE DELETED : NOT EXIST OR HEADER\n", name);
	}
	if (objectToDel == obj || objectToDel == NULL) {
		objectL[0] = NULL;
		objectL[1] = NULL;
	}
	else {
		objectL[1] = objectToDel;
		objectL[0] = previousObject;
	}
	return objectL;
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

	freeblocks = BLOCNUM;

	resetFAT();

	resetVolume();

	supprObjectStruc(obj);

}

void resetFAT()
{
	unsigned  int index;
	for(index = 0 ; index < BLOCNUM ; index++)
		FAT[index] = FREE;
}
void resetVolume()
{
	unsigned int index;
	for(index = 0 ; index < BLOCNUM*BLOCSIZE ; index ++)
		volume[index] = '\0';
}

void supprObjectStruc(struct objet *object)
{
	if(object ->next == NULL)
		free(object);
	else
	{
		supprObjectStruc(object->next);
		free(object);
	}

}

int lire_objet (struct objet *objectTR, char **dataOut) {

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

