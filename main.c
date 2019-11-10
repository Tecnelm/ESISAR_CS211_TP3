#include <stdio.h>
#include "fat.c"

int main() {
    char nom[] = "TP3";
    unsigned short auteur = 7;
    unsigned int taille = 1;
    int data[] = {3,6,6,7,8,10,14,15,17,19,81,21,23,25,26,28,28,28,32,32,34,35,38,38,39,43,44,46,48,49,50,58,59,62,64,65,69,71,75,79,79,79,20,84,86,89,92,93,97,99};

    struct objet newObjet;



    initialise_fat();
    creer_objet( *nom,   auteur,  taille,  *data);


    return 0;
}