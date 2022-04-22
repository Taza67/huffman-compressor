#include <stdio.h>
#include <stdlib.h>
#include "arbre_huffman.h"

void occurence(char *nom_fichier, int tab[256]) {
    int caractere = 0;
    FILE *fichier = NULL;
    if ((fichier = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction occurence(char *nom_fichier, int tab[256]) : ouverture du fichier %s impossible !\n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        while ((caractere = fgetc(fichier)) != EOF) {
            tab[caractere]++;
        }
    }
    fclose(fichier);
}