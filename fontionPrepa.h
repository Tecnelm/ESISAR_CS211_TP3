
typedef struct Node {
    char data ;
    struct node *link ;
} Lnode ;

void insertionTete(Lnode **ph, char item);
void insertionQueue(Lnode **ph,char item);
void suppressionTete(Lnode **ph);
void suppressionQueue(Lnode **ph);
void listeAffiche(Lnode * ptr);
