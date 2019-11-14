#include <stdio.h>

#include "fat.h"
#include  <string.h>


/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/

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

int objectExist (char *nom) {

	struct objet *objTemp;
	objTemp = obj;
	//struct objet *objPrevious;
	//objPrevious = obj;

	while (objTemp != NULL){
		if (!strcmp(objTemp->nom, nom)) {
			return 1;
		}
		objTemp = objTemp->next;
	}

	return 0;
}


struct objet *creer_objet (char *nom, unsigned short auteur, unsigned int taille, char *data) {

	struct objet *objTemp;
	unsigned int nbBlock;
	struct objet *objPrevious;

	int nbBlockTemp;
	int indexed;
	signed int lastIndex;
	unsigned int i, j, l;
	unsigned long reste;
	int indexReste;
	int indexData;

	objPrevious = obj;
	nbBlock = (taille / BLOCSIZE) + 1;

	if (freeblocks >= nbBlock && !objectExist(nom)) {
		freeblocks = freeblocks - nbBlock;

		objTemp = malloc(sizeof(*objTemp));

		if (objTemp == NULL) {
			fprintf(stderr, "error malloc");
			free(objTemp);
			exit(EXIT_FAILURE);
		}

		while (objPrevious->next != NULL) {
			objPrevious = objPrevious->next;
		}

		objPrevious->next = objTemp;

		objTemp->auteur = auteur;
		objTemp->taille = taille;
		objTemp->next = NULL;
		strcpy(objTemp->nom, nom);

		nbBlockTemp = nbBlock;
		indexed = 1;
		lastIndex = -1;
		reste = strlen(data) % BLOCSIZE;
		indexReste = 0;
		indexData = 0;

		for (i = 0; i < BLOCNUM; ++i) {
			if (nbBlockTemp != -1) {
				if (FAT[i] == FREE) {
					if (indexed) {
						objTemp->index = i;
						indexed = 0;
					}
					for (j = 0; j < (BLOCSIZE); ++j) {
						if (nbBlockTemp > 1) {
							volume[(BLOCSIZE * i) + j] = data[(BLOCSIZE * indexData) + j];
						}
						else {
							if (reste > indexReste) {
								volume[(BLOCSIZE * i) + j] = data[(BLOCSIZE * indexData) + j];
								indexReste++;
							}
							else {
								for (l = indexReste; l < (BLOCSIZE - indexReste); l++) {
									volume[(BLOCSIZE * i) + l] = '\0';
								}
							}
						}
					}


					if (lastIndex != -1 && nbBlockTemp != 0) {
						FAT[lastIndex] = i;
					}
					else {
						FAT[lastIndex] = END;
					}
					indexData++;
					nbBlockTemp--;
					lastIndex = i;
				}

			}

		}

		return objTemp;

	}

	fprintf(stderr, "NO PLACE AVAILABLE OR NAME ALREADY USE\n");
	return NULL;

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

	if (objectExist(nom) && strcmp(nom, "first")) {
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

	/*if (objetToDel == NULL) {
		nbBlock = 1;
		freeblocks = freeblocks + nbBlock;
		indexTemp = 0;
	}*/

	nbBlock = (objetToDel->taille / BLOCSIZE) + 1;
	freeblocks = freeblocks + nbBlock;
	indexTemp = objetToDel->index;

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

int lire_objet (struct objet *o, char **data) {
	char * newData;
	int i;
	int l;
	int indexData;
	int indexNewData;
	int nbBlock;

	newData = malloc(o->taille);
	if (newData == NULL) {
		fprintf(stderr, "error malloc");
		free(data);
		exit(EXIT_FAILURE);
	}

	indexNewData = 0;
	indexData = o->index;
	nbBlock = (o->taille / BLOCSIZE) + 1;

	for (i = 0; i < nbBlock; i++) {
		for (l = 0; l < BLOCSIZE; l++) {
			newData[indexNewData] = volume[l + (indexData * BLOCSIZE)];
			indexNewData++;
		}

		indexData = FAT[indexData];
	}
	*data = newData;
	return EXIT_SUCCESS;
}

