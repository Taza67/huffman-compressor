#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocation.h"
#include "en_tete.h"
#include "compression.h"

/* écrit le codage de huffman du fichier à compresser dans l'archive */
void ecrire_codage(FILE* fichier, FILE* archive, noeud* alphabet[256]) {
    int paquet = 0,
        taille_paquet = 0;
    int caractere,
        codage;
    if (archive == NULL) {
        fprintf(stderr, "- Erreur -> fonction ecrire_codage(FILE *fichier, FILE *archive, noeud *alphabet[256]) : archive = NULL !\n");
        exit(EXIT_FAILURE);
    }
    if (fichier == NULL) {
        fprintf(stderr, "- Erreur -> fonction ecrire_codage(FILE *fichier, FILE *archive, noeud *alphabet[256]) : fichier = NULL !\n");
        exit(EXIT_FAILURE);
    }
    fseek(fichier, 0, SEEK_SET);
    while((caractere = fgetc(fichier)) != EOF) {
        paquet = paquet << alphabet[caractere]->bits;
        paquet = paquet | alphabet[caractere]->code;
        taille_paquet += alphabet[caractere]->bits;
        while(taille_paquet >= 8) {
            taille_paquet -= 8;
            codage = paquet >> taille_paquet;
            fputc(codage, archive);
        }
    }
    if (taille_paquet > 0) {
        paquet = paquet << (8 - taille_paquet);
        fputc(paquet, archive);
    }
    fputc('\0', archive);
}

/* compresse un fichier dans une archive */
void compression_fichier(char *nom_archive, char *nom_fichier) {
    FILE *fichier = NULL, *archive = NULL;
    int tab_occurence[256],
        nbr_char = 0,
        taille_fichier = 0,
        i = 0;
    noeud *alphabet[256],
        *arbre_huffman[256];
    for (i = 0; i < 256; i++) {
        tab_occurence[i] = 0;
        alphabet[i] = NULL;
        arbre_huffman[i] = NULL;
    }
    if ((fichier = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction compression_fichier(char* nom_archive, char* nom_fichier) : ouverture du fichier %s impossible !\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    if ((archive = fopen(nom_archive, "wb")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction compression_fichier(char* nom_archive, char* nom_fichier) : ouverture de l'archive %s impossible !\n", nom_archive);
        exit(EXIT_FAILURE);
    }
    fwrite(nom_fichier, sizeof(char), strlen(nom_fichier), archive);
    fputc('\0', archive);
    occurence(nom_fichier, tab_occurence);
    creer_tous_noeuds(arbre_huffman, tab_occurence, &nbr_char, &taille_fichier);
    creer_noeud(arbre_huffman, nbr_char);
    creer_code(*arbre_huffman, 0, 0, alphabet);
    ecrire_entete_aux(archive, alphabet);
    ecrire_codage(fichier, archive, alphabet);
    for (i = 0; i < 256; i++)
        if (alphabet[i] != NULL) libere(alphabet[i]);
    fclose(fichier);
    fclose(archive);
}