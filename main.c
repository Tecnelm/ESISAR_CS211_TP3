#include <stdio.h>
#include "src/fat.h"


int main () {
	//char nomToFind[] = "first";
	char nom[] = "second";
	unsigned short auteur = 7;
//	char data[] = "vxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE Est ";
	char data[] = "bonjoure";
	unsigned int taille = sizeof(data);
	char *readData;

	struct objet *objTemp;

	initialise_fat();
	creer_objet(nom, auteur, taille, data);
	objTemp = rechercher_objet("second");


	printObject(objTemp);

	objTemp = rechercher_objet("first");

	printObject(objTemp);
	objTemp = rechercher_objet(nom);
	lire_objet(objTemp, &readData);
	//supprimer_objet(nom);

//	printObject(objTemp);

//	objTemp = rechercher_objet("first");
//	printObject(objTemp);


	printf("%s\n", readData);

	supprimer_tout();
	free(readData);
	return 0;
}
