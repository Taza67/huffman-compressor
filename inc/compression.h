#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "arbre_huffman.h"
#include "gestion_fichiers.h"

/* écrit le codage de huffman du fichier à compresser dans l'archive */
void ecrire_codage(FILE* fichier, FILE* archive, noeud* alphabet[256]);

/* compresse un fichier dans une archive déjà ouverte */
void compression_fichier(FILE *archive, file struct_fichier, noeud *alphabet[256]);

/* compresse une liste de fichiers dans une archive */
void compression(file * liste_fichiers, int nombre_fichiers, char *nom_archive);

#endif