#include <stdio.h>
#include "src/fat.h"


int main () {
	//char nomToFind[] = "first";
	char nom[] = "second";
	unsigned short auteur = 7;
//	char data[] = "vxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE Est ";
	char data[] = "bonjoure j!";
	unsigned int taille = sizeof(data)-1;
	char *readData;

	struct objet *objTemp;

	initialise_fat();
	objTemp = rechercher_objet("first");
	printObject(objTemp);

	creer_objet(nom, auteur, taille, data);
	objTemp = rechercher_objet(nom);
	printObject(objTemp);


	lire_objet(objTemp, &readData);

	supprimer_objet(nom);

	printf("%s\n", readData);

	supprimer_tout();
	free(readData);
	return 0;
}
