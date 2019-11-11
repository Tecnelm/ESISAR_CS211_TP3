#include <stdio.h>
#include "src/fat.h"


int main () {

	char nom[] = "first";

	unsigned short auteur = 7;
	char data[] = "je moupel pedro carahol!";
	unsigned int taille = sizeof(data);


	struct objet *objTemp;

	initialise_fat();
	//creer_objet(nom, auteur, taille, data);

	objTemp = rechercher_objet("first");
	printf("%s", objTemp->nom);


	return 0;
}