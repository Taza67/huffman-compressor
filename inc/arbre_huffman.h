#ifndef _ARBRE_HUFFMAN_H_
#define _ARBRE_HUFFMAN_H_

/* Structure d'un noeud de l'arbre de huffman */
typedef struct struct_noeud {
    int initial;                /* Caractere */
    int occurence;
    int code;                   /* code binaire */
    int bits;                   /* Nombre de bits du code */
    struct struct_noeud * gauche; /* fils gauche */
    struct struct_noeud * droit;  /* fils droit */
} noeud;

/* Compte le nombre d'occurence de chaque caractère d'un fichier
   et les mets dans le tableau tab */
void occurence(char *nom_fichier, int tab[256]);

#endif