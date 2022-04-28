#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "arbre_huffman.h"

/* écrit le codage de huffman du fichier à compresser dans l'archive */
void ecrire_codage(FILE* fichier, FILE* archive, noeud* alphabet[256]);

/* compresse un fichier dont le nom a été donné dans une archive */
void compression_fichier(char *nom_archive, char *nom_fichier);

#endif