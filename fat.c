#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fat.h"
#include "math.h"

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/

void initialise_fat() {
    int i;
    for (i = 0; i < BLOCNUM; i++) {
        FAT[i] = 0xFFFF;
    }
    freeblocks = BLOCNUM;

    /*obj = malloc(sizeof(*obj));
    if(obj == NULL) {
        fprintf(stderr, "Chained list empty");
        free(obj);
        exit(EXIT_FAILURE);
    }*/
}

struct objet *rechercher_objet(char *nom){

    while(obj->next != NULL) {
        obj = obj->next;
        if (obj->nom == nom) {
            return obj;
        }
    }
    return NULL;
}
struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data){
    int nbBlock;
    nbBlock = (taille/512)+1;

    if(freeblocks>=nbBlock) {
        freeblocks = freeblocks - nbBlock;

        obj = malloc(sizeof(*obj));
        if (obj == NULL) {
            fprintf(stderr, "Chained list empty");
            free(obj);
            exit(EXIT_FAILURE);
        }

        obj->nom[NAMELEN] = nom;
        obj->auteur = auteur;
        obj->taille = taille;

        unsigned int nbBlockTemp;
        int indexed;
        signed int lastIndex;
        int i,j;

        nbBlockTemp = nbBlock;
        indexed = 1;
        lastIndex = -1;


        for (i = 0; i < BLOCNUM; ++i) {
            if(!nbBlockTemp){
                if(FAT[i] == FREE){
                    if(indexed){
                        obj->index = i;
                        indexed = 0;
                    }
                    for (j = (512*(taille-nbBlockTemp)); j < (512*(taille-nbBlockTemp)+512) ; ++j) {
                        if(data[j] != NULL)
                            volume[512 * i] = data[j];
                        else
                            volume[512 * i] = END;
                    }
                    if(lastIndex != -1){
                        FAT[lastIndex] = i;
                    }
                    lastIndex = i;
                }
                nbBlockTemp--;
            }

        }
        exit(EXIT_SUCCESS);
    }
    else {
        fprintf(stderr,"no more place");
        exit(EXIT_FAILURE);
    }
}
