#include <stdio.h>
#include "src/fat.h"


int main () {
	char nomToFind[] = "first";
	char nom[] = "second";
	unsigned short auteur = 7;
	char* data = "vxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE Est ";
	unsigned int taille = sizeof("vxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE EstxEnOphOn histoRIeN GrAvE Et du pReMIEr rAng ENtRe lEs GRecS a FaIT Un lIvre Auquel iL FaiT pArLER sImoniDe avec hIErsOn tiRAn dE sYraCuse des MIseREs dU TiRAN : Ce LIvRE Est ");


	struct objet *objTemp;

	initialise_fat();


	objTemp = creer_objet(nom, auteur, taille, data);
	//objTemp = rechercher_objet(nom);


	printf("nom : %s \n", objTemp->nom);
	printf("taille : %u \n", objTemp->taille);
	printf("auteur : %u \n", objTemp->auteur);
	printf("index : %u \n", objTemp->index);

	supprimer_objet(nom);

	objTemp = rechercher_objet(nom);


	printf("nom : %s \n", objTemp->nom);
	printf("taille : %u \n", objTemp->taille);
	printf("auteur : %u \n", objTemp->auteur);
	printf("index : %u \n", objTemp->index);

	return 0;
}