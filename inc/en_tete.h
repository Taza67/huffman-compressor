#ifndef _TETE_H_
#define _TETE_H_

#include "arbre_huffman.h"

/* Fonction qui écrit l'entete dans l'archive */
void ecrire_entete_aux(FILE* archive, noeud* alphabet[256]);

/* Récupère l'entete de l'archive */
void recuperer_entete(FILE* archive, int occurence[256]);

#endif