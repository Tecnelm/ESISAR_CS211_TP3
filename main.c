#include <stdio.h>
#include "src/fat.h"


int main () {

	char nom[] = "first";
	char nom2[] = "frfst";
	unsigned short auteur = 7;
	char data[] = "je moupel pedro carahol!";
	unsigned int taille = sizeof(data);

	//char* pnom;
	//pnom = &nom;

	struct objet *objTemp;

	initialise_fat();
	creer_objet(nom, auteur, taille, data);

	objTemp = rechercher_objet('first');
	printf("%d", objTemp->taille);


	return 0;
}