#include <stdio.h>
#include "src/fat.h"


int main () {
	//char nomToFind[] = "first";
	char nom1[] = "second";
	char data1[] = "bonjoure j!";
	char nom2[] = "third";
	char data2[] = "bonjoure j!";
	char nom3[] = "fourth";
	char data3[] = "bonjoure j!";
	char nom4[] = "fifth";
	char data4[] = "c'est une longue phrase que je vois la;";

	unsigned short auteur = 7;
	char *readData;

	struct objet *objTemp;

	initialise_fat();
	//objTemp = rechercher_objet("first");
	//printObject(objTemp);

	creer_objet(nom1, auteur, (sizeof(data1)-1), data1);
	objTemp = rechercher_objet(nom1);
	printObject(objTemp);

	creer_objet(nom2, auteur, (sizeof(data2)-1), data2);
	objTemp = rechercher_objet(nom2);
	printObject(objTemp);

	creer_objet(nom3, auteur, (sizeof(data3)-1), data3);
	objTemp = rechercher_objet(nom3);
	printObject(objTemp);



	supprimer_objet(nom2);

	creer_objet(nom4, auteur, (sizeof(data4)-1), data4);
	objTemp = rechercher_objet(nom4);
	printObject(objTemp);

	lire_objet(objTemp, &readData);
	printf("%s\n", readData);

	supprimer_tout();
	free(readData);
	return 0;
}
