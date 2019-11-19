#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node {
	char data ;
	struct Node *link ;
} Lnode ;

void insertionTete(Lnode **ph, char item);
void insertionQueue(Lnode **ph,char item);
void suppressionTete(Lnode **ph);
void suppressionQueue(Lnode **ph);
void listeAffiche(Lnode * ptr);
;