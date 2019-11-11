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

	struct objet objTemp;

	strcpy(objTemp.nom,"first");
	objTemp.taille = 0;
	objTemp.auteur = 0;
	objTemp.index = 0;
	objTemp.next = NULL;

	obj = &objTemp;

}

struct objet *rechercher_objet (char nom[]) {

	while (obj != NULL) {
		if (compareStr(obj->nom, nom)) {
			return obj;
		}
		obj = obj->next;
	}
	return NULL;
}

int compareStr (char a[], char b[]) {

	int tailleA = strlen(a);
	int tailleB = strlen(b);
	int i;

	if (tailleA != tailleB) {
		return 0;
	}
	for (i = 0; i < tailleA; ++i) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}


struct objet *creer_objet (char *nom, unsigned short auteur, unsigned int taille, char *data) {

	int nbBlock;
	nbBlock = (taille / 512) + 1;

	if (freeblocks >= nbBlock) {
		freeblocks = freeblocks - nbBlock;

		/*obj = malloc(sizeof(*obj));
		if (obj == NULL) {
			fprintf(stderr, "Chained list empty");
			free(obj);
			exit(EXIT_FAILURE);
		}*/
		struct objet objTemp;

		//objTemp.nom[NAMELEN] = nom;
		strcpy(objTemp.nom,nom);
		objTemp.auteur = auteur;
		objTemp.taille = taille;
		objTemp.next = NULL;

		unsigned int nbBlockTemp;
		int indexed;
		signed int lastIndex;
		int i, j;
		int reste;
		int indexReste;

		nbBlockTemp = nbBlock;
		indexed = 1;
		lastIndex = -1;
		reste = 512 % nbBlock;
		indexReste = 0;

		for (i = 0; i < BLOCNUM; ++i) {
			if (!nbBlockTemp) {
				if (FAT[i] == FREE) {
					if (indexed) {
						objTemp.index = i;
						indexed = 0;
					}
					for (j = (512 * (taille - nbBlockTemp)); j < (512 * (taille - nbBlockTemp) + 512); ++j) {
						if (nbBlockTemp > 1) {
							volume[512 * i] = data[j];
						}
						else {
							if (reste < indexReste) {
								volume[512 * i] = data[j];
								indexReste++;
							}
							else {
								volume[512 * i] = 0;
							}
						}
					}
					if (lastIndex != -1) {
						FAT[lastIndex] = i;
					}
					else if ((taille - nbBlockTemp) == 0) {
						FAT[lastIndex] = END;
					}

					lastIndex = i;
				}
				nbBlockTemp--;
			}

		}

		objTemp.next = obj;
		obj = &objTemp;

		exit(EXIT_SUCCESS);

	}
	else {
		fprintf(stderr, "no more place or name already exist");
		exit(EXIT_FAILURE);
	}
}
