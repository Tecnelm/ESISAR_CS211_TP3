#include <stdlib.h>
#include <stdio.h>

#include "fat.h"
#include  <string.h>


/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/

void initialise_fat () {

	int i;
	for (i = 0; i < BLOCNUM; i++) {
		FAT[i] = 0xFFFF;
	}
	freeblocks = BLOCNUM;

	struct objet* objTemp;
	objTemp = malloc(sizeof(*objTemp));

	if(objTemp == NULL ){
		fprintf(stderr,"error malloc");
		free(objTemp);
		exit(EXIT_FAILURE);
	}

	strcpy(objTemp->nom,"first");
	objTemp->taille = 0;
	objTemp->auteur = 0;
	objTemp->index = 0;
	objTemp->next = NULL;

	obj = objTemp;

}

struct objet *rechercher_objet (char *nom) {

	struct objet* objTemp;
	objTemp = malloc(sizeof(*objTemp));

	if(objTemp == NULL ){
		fprintf(stderr,"error malloc");
		free(objTemp);
		exit(EXIT_FAILURE);
	}
	objTemp = obj;

	while (objTemp != NULL) {
		if (strcmp(objTemp->nom, nom) == 0) {
			return objTemp;
		}
		objTemp = objTemp->next;
	}
	fprintf(stderr, "Non-inexistent object \n");
	return NULL;
}

int rechercher_objet_bool (char* nom) {

	struct objet* objTemp;
	objTemp = malloc(sizeof(*objTemp));

	if(objTemp == NULL ){
		fprintf(stderr,"error malloc");
		free(objTemp);
		exit(EXIT_FAILURE);
	}
	objTemp = obj;

	while (objTemp != NULL) {
		if (strcmp(objTemp->nom, nom) == 0) {
			return 0;
		}
		objTemp = objTemp->next;
	}

	return 1;
}


struct objet *creer_objet (char *nom, unsigned short auteur, unsigned int taille, char *data) {

	unsigned int nbBlock;
	nbBlock = (taille / 512) + 1;

	if (freeblocks >= nbBlock && rechercher_objet_bool(nom)) {
		freeblocks = freeblocks - nbBlock;

		struct objet* objTemp;
		objTemp = malloc(sizeof(*objTemp));

		if(objTemp == NULL ){
			fprintf(stderr,"error malloc");
			free(objTemp);
			exit(EXIT_FAILURE);
		}

		objTemp->auteur = auteur;
		objTemp->taille = taille;
		obj->next = objTemp;
		objTemp->next = NULL;
		strcpy(objTemp->nom, nom);


		int nbBlockTemp;
		int indexed;
		signed int lastIndex;
		int i, j;
		int reste;
		int indexReste;

		nbBlockTemp = nbBlock;
		indexed = 1;
		lastIndex = -1;
		reste = strlen(data) % 512;
		indexReste = 0;

		for (i = 0; i < BLOCNUM; ++i) {
			if (nbBlockTemp != -1) {
				if (FAT[i] == FREE) {
					if (indexed) {
						objTemp->index = i;
						indexed = 0;
					}
					for (j = (512 * (nbBlock - nbBlockTemp)); j < (512 * (nbBlock - nbBlockTemp) + 512); ++j) {
						if (nbBlockTemp > 1) {
							volume[(512 * i)+(j-(512 * (nbBlock - nbBlockTemp)))] = data[j];
						}
						else {
							if (reste >= indexReste) {
								volume[(512 * i)+(j-(512 * (nbBlock - nbBlockTemp)))] = data[j];
								indexReste++;
							}
							else {
								volume[512 * i] = 0;
							}
						}
					}
					if (lastIndex != -1 && nbBlockTemp != 0) {
						FAT[lastIndex] = i;
					}
					else {
						FAT[lastIndex] = END;
					}

					lastIndex = i;
				}
				nbBlockTemp--;
			}

		}

		return objTemp;

		exit(EXIT_SUCCESS);

	}
	else {
		fprintf(stderr, "no more place or name already exist");
		exit(EXIT_FAILURE);
	}
}

int supprimer_objet(char *nom){
	struct objet* objNom;
	struct objet* objBeforeNom;
	struct objet* objAfterNom;
	objNom = malloc(sizeof(*objNom));
	objBeforeNom = malloc(sizeof(*objAfterNom));
	objAfterNom = malloc(sizeof(*objAfterNom));

	if(objNom == NULL || objBeforeNom == NULL|| objAfterNom == NULL){
		fprintf(stderr,"error malloc");
		free(objNom);
		free(objBeforeNom);
		free(objAfterNom);
		exit(EXIT_FAILURE);
	}
	objNom = obj;

	int indexObjNom;
	indexObjNom = 0;
	if(rechercher_objet_bool(nom) == 0 && strcmp(nom,"first") != 0){
		while (objNom != NULL) {
			indexObjNom++;
			if (strcmp(objNom->nom, nom) == 0) {
				break;
			}
			objNom = objNom->next;
		}
	}
	else{
		fprintf(stderr,"%s does not exist or you are trying to delete the initial object 'first'", nom);
	}

	unsigned int nbBlock;
	nbBlock = (objNom->taille / 512) + 1;

	freeblocks = freeblocks + nbBlock;

	unsigned short indexTemp = obj->index;
	unsigned short lastIndexTemp;
	int k;
	int l;
	for ( k = 0; k < (nbBlock) ; ++k) {
		if (indexTemp != END) {
			for (l = 512 * indexTemp; l < (512 * indexTemp + 512); l++) {
				volume[l] = 0;
			}
			lastIndexTemp = indexTemp;
			indexTemp = FAT[indexTemp];
		}
		FAT[lastIndexTemp] = FREE;
	}




	int i;
	int j;
	for (i = 0; i < (indexObjNom-1); ++i) {
		objBeforeNom = objBeforeNom->next;
	}
	for (j = 0; j < (indexObjNom+1); ++j) {
		objAfterNom = objAfterNom->next;
	}

	objBeforeNom->next = objAfterNom;
	free(objNom);
	exit(EXIT_SUCCESS);

}
