#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fontionPrepa.h"

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/


/* Insertion en "tête de liste" */
void insertionTete(Lnode **ph, char item){
    Lnode *newNode = malloc(sizeof(*newNode));

    if(newNode == NULL || ph == NULL){
        fprintf(stderr,"Chained list empty");
        exit(EXIT_FAILURE);
    }

    newNode->data = item;

    newNode->link = *ph;
    *ph = newNode;
}

/* Insertion en "queue de liste" */
void insertionQueue(Lnode **ph,char item)	{
    Lnode *newNode = malloc(sizeof(*newNode));

    if(newNode == NULL || ph == NULL){
        fprintf(stderr,"Chained list empty");
        exit(EXIT_FAILURE);
    }

    newNode->data = item;

    newNode->link = NULL;
    ph* =
}

/* Suppression en "tête de liste" */
void suppressionTete(Lnode **ph){
	/* A compléter */
	}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
	/* A compléter */
	}

/* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode  *ptr){
	if ( NULL == ptr )
		printf("Liste vide!") ;
	else 
		printf("Contenu de la liste : ") ;
	while ( NULL != ptr ) 	{
		printf("%c ",ptr->data);
		ptr = ptr->link ;
		}
	printf("\n") ;
}

