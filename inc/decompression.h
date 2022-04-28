#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "arbre_huffman.h"

/* Récupère le contenu du fichier d'origine à partir du codage binaire dans l'archive */
void recuperer_contenu(FILE* archive, FILE* fichier, noeud* arbre_huffman[], int taille_fichier);

/* Renvoie une feuille dès qu'un code correspond au sien */
noeud * recuperer_feuille(noeud *racine, int paquet, int taille_paquet, int profondeur);

/* Décompresse un fichier dans un dossier cible qui est par défaut le dossier local */
void decompression_fichier(char * nom_archive, char *dossier_cible);

#endif