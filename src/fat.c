#include "fat.h"


#define BLOCSIZE 512
#define BLOCNUM 1024
#define NAMELEN 256
#define FREE 0xFFFF
#define END 0xFFFE


/**
 * structure of ou objectFat
 * taille correspond to the size of data
 * index the index of first indexFAT
 * next point to the next item of the list
 * auteur who write the data
 * name of the bloc
 */
struct objet {
	char nom[NAMELEN];
	unsigned int taille;
	unsigned short auteur;
	unsigned short index;
	struct objet *next;
};

struct objet *obj;

char volume[BLOCSIZE * BLOCNUM];

unsigned short FAT[BLOCNUM];

unsigned short freeblocks;

struct objet *new_object () {

	struct objet *objTemp;
	objTemp = malloc(sizeof(*objTemp));/// allocate the number of byte you need for the object

	if (objTemp == NULL) {
		fprintf(stderr, "ERROR ALLOCATION MEMORY\n");
		free(objTemp);
		exit(EXIT_FAILURE);
	}
	return objTemp;
}

void initialise_fat () {

	struct objet *objTemp;

	resetFAT();/// write all index of FAT to FREE

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
		if (!strcmp(objTemp->nom, nom)) {
			return objTemp;                    ///return the object with the right name
		}
		objTemp = objTemp->next;
	}
	fprintf(stderr, "NO OBJECT FUND\n");
	return NULL;
}

int objectNotExist (char *nom) {

	struct objet *objTemp;
	objTemp = obj;

	while (objTemp != NULL) {///look every object to see if the name is present
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

	///calcul the needed by the data
	blocUse = (taille / BLOCSIZE);
	rest = taille % BLOCSIZE;

	if (rest) {///add one bloc  if you have other data (a rest of data)
		blocUse++;
	}

	///check if you have enough place left
	if ((freeblocks < blocUse)) {
		fprintf(stderr, "ERROR NO PLACE LEFT\n");
		return EXIT_FAILURE;
	}
	else if (!objectNotExist(nom)) {
		fprintf(stderr, "OBJECT ALREADY EXIST\n");
		return EXIT_FAILURE;
	}
	newObject = malloc(sizeof(struct objet));
	if (rest) {///get the number of full packet
		blocUse--;
	}

	if (newObject == NULL) {
		fprintf(stderr, "ALLOCATION MEMORY ERROR\n");
		free(newObject);
		supprimer_tout();
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
		writeBloc(indexFat, data, BLOCSIZE, indexWriteBloc);/// write data by bloc
		if (indexWriteBloc == blocUse - 1 && !rest) {
			FAT[indexFat] = END;
		}
		else {
			FAT[indexFat] = nextFatFreeIndex(indexFat + 1); /// get the next free indexFat
		}
		indexFat = FAT[indexFat];

	}

	if (rest) {/// write the rest of the data
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
	while (index < BLOCNUM && FAT[index] != FREE) {///look what's the next index
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
		tempByte = fullData[packetNumber * BLOCSIZE + index];/// get the right byte indication with packetnumber
		volume[fatIndex * BLOCSIZE + index] = tempByte;/// start the write at the the position indicate with fat index, and write each byte
	}
	freeblocks--;
	return EXIT_SUCCESS;
}

void insertObject (struct objet *header, struct objet *newObjet) {

	struct objet *objetTemp;
	objetTemp = header;
	while (objetTemp->next != NULL) {
		objetTemp = objetTemp->next;/// put the adress of ofbject at the last position
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

	objectsList[0]->next = objectsList[1]->next; /// make the joint between the object point by the one deleted and the one who point on the one we delete

	nbBlock = (objectsList[1]->taille) / BLOCSIZE + ((objectsList[1]->taille) % BLOCSIZE == 0 ? 0 : 1); /// calculate how many bloc we have to free

	freeFat(objectsList[1]->index); ///free all fat index use by this item

	freeblocks += nbBlock;

	free(objectsList[1]); /// free our object

	return EXIT_SUCCESS;

}

void freeFat (unsigned int firstIndex) {

	unsigned int indexFat = firstIndex;

	while (FAT[indexFat] != END) { ///look all index point by the first index and free them
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
			previousObject = objectToDel;/// initialise the the previous object
			objectToDel = objectToDel->next; /// get the next index
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
		objectL[0] = previousObject;
		objectL[1] = objectToDel;
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

	resetFAT();/// set all FAT index to FREE

	resetVolume(); /// reset the volume not needed, we write on each bit \0

	supprObjectStruc(obj);

}

void resetFAT () {

	unsigned int index;
	for (index = 0; index < BLOCNUM; index++) {
		FAT[index] = FREE;
	}
}

void resetVolume () {

	unsigned int index;
	for (index = 0; index < BLOCNUM * BLOCSIZE; index++) {
		volume[index] = '\0';
	}
}

void supprObjectStruc (struct objet *object) {

	if (object->next == NULL) {
		free(object);
	}
	else {
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
		readBloc(indexFat, BLOCSIZE, *dataOut, index);/// read each bloc of data
		indexFat = FAT[indexFat];
	}
	if (rest) {/// get the data in the last bloc if the packet is not full
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
	for (index = 0; index < size; index++) {/// read each byte and write them in our char*
		str[BLOCSIZE * numberPacket + index] = volume[BLOCSIZE * indexFat + index];
	}
	return EXIT_SUCCESS;
}

