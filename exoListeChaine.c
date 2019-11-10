#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fontionPrepa.h"

/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/


/* Insertion en "t�te de liste" */
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

/* Suppression en "t�te de liste" */
void suppressionTete(Lnode **ph){
	/* A compl�ter */
	}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
	/* A compl�ter */
	}

/* Proc�dure d'affichage de la liste. Ne doit pas �tre modifi�e!!! */
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

