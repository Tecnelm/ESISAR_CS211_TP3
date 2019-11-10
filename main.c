//include <stdio.h>
#include "fat.h"
#include "exoListeChaine.c"


int main(void) {
    Lnode *tete = NULL ;

    listeAffiche(tete) ;
    insertionTete(&tete,'a') ;
    listeAffiche(tete) ;
    insertionTete(&tete,'c') ;
    listeAffiche(tete) ;
    insertionQueue(&tete,'t') ;
    listeAffiche(tete) ;
    insertionQueue(&tete,'s') ;
    listeAffiche(tete) ;
    suppressionTete(&tete) ;
    listeAffiche(tete) ;
    suppressionTete(&tete) ;
    listeAffiche(tete) ;
    suppressionQueue(&tete) ;
    listeAffiche(tete) ;
    suppressionTete(&tete) ;
    listeAffiche(tete) ;

    return EXIT_SUCCESS;
}
