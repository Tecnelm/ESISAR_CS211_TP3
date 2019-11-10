#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fat.h"

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/

void initialise_fat() {
    int i;
    for (i = 0; i < BLOCNUM; i++) {
        FAT[i] = 0xFFFF;
    }
    freeblocks = BLOCNUM;

    obj = malloc(sizeof(*obj));
    if(obj == NULL) {
        fprintf(stderr, "Chained list empty");
        free(obj);
        exit(EXIT_FAILURE);
    }
}

struct objet *rechercher_objet(char *nom){


}