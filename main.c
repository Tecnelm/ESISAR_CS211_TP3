#include <stdio.h>
#include "src/fat.h"


int main () {

	char nom[] = "second";
	unsigned short auteur = 7;
	char data[] = "je moupel pedro carahol!";
	unsigned int taille = sizeof(data);

	struct objet *objTemp;

	initialise_fat();


	//objTemp = rechercher_objet("first");
	objTemp = creer_objet(nom, auteur, taille, data);

	printf("nom : %s \n", objTemp->nom);
	printf("taille : %u \n", objTemp->taille);
	printf("auteur : %u \n", objTemp->auteur);
	printf("index : %u \n", objTemp->index);





	return 0;
}