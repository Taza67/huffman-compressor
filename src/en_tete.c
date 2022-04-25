#include <stdio.h>
#include <stdlib.h>
#include "arbre_huffman.h"
#include "en_tete.h"

void ecrire_entete_aux(FILE* archive, noeud* alphabet[256]) {
    int i;
    if (archive == NULL) {
        fprintf(stderr, "- Erreur -> fonction ecrire_entete(FILE *archive, noeud *alphabet[256]) : archive = NULL !\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < 256; i++) {
        if (alphabet[i] != NULL) {
            fwrite(&i, sizeof(char), 1, archive);
            fwrite(&(alphabet[i]->occurence), sizeof(int), 1, archive);
        }
    }
    fputc('\0', archive);
} 

void recuperer_entete(FILE* archive, int occurence[256]) {
    int caractere;
    do {
        caractere = fgetc(archive);
        if (caractere != '\0' && caractere != EOF) {
            if (fread(&(occurence[caractere]), sizeof(int), 1, archive) != 1)
                fprintf(stderr, "- Erreur recuperer_entete(FILE* archive, int occurence[256]) : recupération de l'occurence échouée !\n");
        }
    } while (caractere != '\0' && caractere != EOF);
}