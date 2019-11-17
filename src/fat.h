#include <stdio.h>
#include <stdlib.h>
#include  <string.h>


#define BLOCSIZE 512
#define BLOCNUM 1024
#define NAMELEN 256
#define FREE 0xFFFF
#define END 0xFFFE


/**
 * structure of ou objectFat
 * taille correspond to the size of data
 * index the index of first indexFAT
 * next point to the next item of the list
 * auteur who write the data
 * name of the bloc
 */
struct objet;

/**
 * print all data of an object (take care do not print the data)
 * @param obj
 */
void printObject (struct objet *obj);

/**
\brief Cette fonction permet de créer un objet en vérifiant qu'aucun objet n'a le même nom dans la liste (pas triée par nom)
si possible, de réserver des blocs dans le tableau FAT et de copier les données (data) dans ces blocs.
mettre à jour la variable freeblocks
\param nom nom de l'objet
\param auteur proprietaire de l'objet
\param taille la taille de l'objet
\param data les données à copier
*/
int creer_objet (char *nom, unsigned short auteur, unsigned int taille, char *data);

/**
 * write a packet of data depends of dataSize
 * @param fatIndex the fat index where we write
 * @param fullData the entire char* of folder
 * @param dataSize the number of byte you have to write
 * @param packetNumber: the current nomber packet of data
 * @return -1 in case of fail 0 else
 */
int writeBloc (unsigned int fatIndex, const char *fullData, unsigned int dataSize, unsigned int packetNumber);

/**
 * Same as writeBloc  but for reading
 * @param indexFat
 * @param size num of byte you will read (not higher than blocsize)
 * @param str the char to put the data
 * @param numberPacket
 * @return
 */
int readBloc (unsigned int indexFat, unsigned int size, char *str, unsigned int numberPacket);

/**
 * get the next indexFAT free
 * @param currentFatIndex
 * @return
 */
unsigned int nextFatFreeIndex (unsigned int currentFatIndex);

/**
 * insert an object to the end of the structur
 * @param header
 * @param newObjet
 */
void insertObject (struct objet *header, struct objet *newObjet);

/**
 * initialise the header
 * @return
 */
struct objet *new_object ();

/**
 * check if an object dont exist
 * @param nom
 * @return 1 if not exist 0 else
 */
int objectNotExist (char *nom);


/**
\brief Cette fonction permet :
D'initialiser le tableau FAT en déclarant tous les blocs libres.
D'initialiser la variable freeblocks à BLOCNUM.
D'initialiser la variable obj
*/
void initialise_fat ();


/**
\brief Cette fonction permet de rechercher un objet par son nom dans la liste chaînée décrivant les objets
\param nom nom de l'objet à rechercher
\return pointeur vers l'objet trouvé ou NULL sinon.
*/
struct objet *rechercher_objet (char *nom);

/**
\brief  Cette fonction permet de supprimer un objet trouvé par son nom, de libérer les blocs dans le tableau FAT, et de mettre à jour la variable freeblocks
\param nom
\return -1 si erreur, 0 sinon.
*/
int supprimer_objet (char *nom);


/**
\brief Cette fonction permet :
De supprimer l'ensemble des objets
De liberer l'ensemble des blocs dans le tableau FAT
De modifier la variable freeblocks
*/
void supprimer_tout ();

/**
 * Get a list of object , list size is 2
 * the first element is the previous object and the next one is the object whith his name passed
 * @param name
 * @return list of 2 elements the first element is the previous object and the next one is the object whith his name passed
 */
struct objet **getObjects (char *name);

/**
 * free all index where data was write with the first index
 * @param firstIndex
 */
void freeFat (unsigned int firstIndex);

/**
 * reformat all fat index to signal them free
 */
void resetFAT ();

/**
 * write all index of volume to \0
 */
void resetVolume ();

/**
 * recursive to free all object tree
 * @param object
 */
void supprObjectStruc (struct objet *object);

/** POUR LES PLUS RAPIDES ..................** BONUS ** BONUS ** BONUS **
\brief Cette fonction permet :
De lire le contenu d'un objet et de le copier dans une structure de données allouée dynamiquement
Attention à la taille !!!!!!!!!!!!!!
\param nom nom de l'objet
\return -1 si erreur, 0 sinon.
*/
int lire_objet (struct objet *o, char **data);
