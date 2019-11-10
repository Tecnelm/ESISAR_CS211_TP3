#include <stdio.h>
#include "fat.c"

int main() {
    char nom[] = "TP3";
    unsigned short auteur = 7;
    unsigned int taille = 1;
    char data[] = "je moupel pedro carahol!";

    struct objet newObjet;



    initialise_fat();
    creer_objet( nom,   auteur,  taille,  data);

    newObjet =  rechercher_objet(nom);


    return 0;
}