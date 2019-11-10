#include "exoListeChaine.h"

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
    Lnode *lastNode = malloc(sizeof(*lastNode));

    if(newNode == NULL || ph == NULL || lastNode == NULL){
        fprintf(stderr,"Chained list empty");
        exit(EXIT_FAILURE);
    }

    lastNode = *ph;
    while(lastNode->link !=NULL){
        lastNode = lastNode->link;
    }

    newNode->data = item;

    newNode->link = NULL;
    lastNode->link = newNode;

    //free(lastNode); //we should free the memory space but it's bug
}

/* Suppression en "t�te de liste" */
void suppressionTete(Lnode **ph){
    Lnode *firstNode = malloc(sizeof(*firstNode));

    if(firstNode == NULL || ph == NULL){
        fprintf(stderr,"Chained list empty");
        exit(EXIT_FAILURE);
    }
    firstNode = *ph;

    *ph = firstNode->link;
    free(firstNode);
}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
    int indexBeforeLast;
    indexBeforeLast = 0;

    Lnode *lastNode = malloc(sizeof(*lastNode));
    Lnode *beforeLastNode = malloc(sizeof(*beforeLastNode));

    if(lastNode == NULL || ph == NULL || beforeLastNode == NULL){
        fprintf(stderr,"Chained list empty");
        exit(EXIT_FAILURE);
    }

    lastNode = *ph;
    beforeLastNode = *ph;

    while(lastNode->link !=NULL){
        lastNode = lastNode->link;
        indexBeforeLast++;
    }
    int i;
    for ( i = 0;  i<(indexBeforeLast-1) ; i++) {
        beforeLastNode = beforeLastNode->link;
    }
    free(lastNode);
    beforeLastNode->link = NULL;

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

