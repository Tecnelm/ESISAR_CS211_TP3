#include <stdio.h>
#include "fat.c"

int main() {
    char nom[] = "TP3";
    unsigned short auteur = 7;
    char data[] = "je moupel pedro carahol!";
    unsigned int taille = sizeof(data);


    struct objet *objTemp;



    initialise_fat();
    creer_objet( nom,   auteur,  taille,  data);

    objTemp =  rechercher_objet(nom);
    printf("%d",objTemp->taille);


    return 0;
}