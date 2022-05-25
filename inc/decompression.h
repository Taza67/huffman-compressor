#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "arbre_huffman.h"

/* Récupère le contenu du fichier d'origine à partir du codage binaire dans l'archive */
void recuperer_contenu(FILE* archive, FILE* fichier, noeud* arbre_huffman[], int taille_fichier);

/* Renvoie une feuille dès qu'un code correspond au sien */
noeud * recuperer_feuille(noeud *racine, int paquet, int taille_paquet, int profondeur);

/* Lit le nom d'une entrée depuis l'archive */
char * recuperer_nom_fichier(FILE* archive);

/* Décompresse un fichier à partir d'une archive */
void decompression_fichier(FILE *archive, char * nom_fichier, noeud* arbre_huffman[256]);

/* Décompresse une archive qui contient une liste de fichiers */
void decompression(char *nom_archive, char *dossier_cible);

#endif