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

/* compresse un fichier dans une archive déjà ouverte */
void compression_fichier(FILE *archive, file struct_fichier, noeud *alphabet[256]) {
    FILE *fichier = NULL;
    if ((fichier = fopen(struct_fichier.nom, "r")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction compression_fichier(FILE* archive, char* nom_fichier) : ouverture du fichier %s impossible !\n", struct_fichier.nom);
        exit(EXIT_FAILURE);
    }
    if (archive == NULL) {
        fprintf(stderr, "- Erreur -> fonction compression_fichier(FILE* archive, char* nom_fichier) : archive = NULL !\n");
        exit(EXIT_FAILURE);
    }
    ecrire_codage(fichier, archive, alphabet);
    fclose(fichier);
}

/* compresse une liste de fichiers dans une archive */
void compression(file * liste_fichiers, int nombre_fichiers, char *nom_archive) {
    FILE *archive = NULL;
    int i = 0;
    noeud *alphabet[256];
    if ((archive = fopen(nom_archive, "wb")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction compression(file * liste_fichiers, int nombre_fichiers, char * nom_archive) : ouverture de l'archive %s impossible !\n", nom_archive);
        exit(EXIT_FAILURE);
    }
    ecrire_entete(liste_fichiers, archive, nombre_fichiers, alphabet);
    fwrite(&(nombre_fichiers), sizeof(int), 1, archive);
    for (i = 0; i < nombre_fichiers; i++) {
        fputc(liste_fichiers[i].type, archive);
        fputc('\0', archive);
        fwrite(liste_fichiers[i].nom, sizeof(char), strlen(liste_fichiers[i].nom), archive);
        fputc('\0', archive);
        if (liste_fichiers[i].type == 'f') {
            liste_fichiers[i].taille = total_occurence_fichier(liste_fichiers[i].nom);
            fwrite(&(liste_fichiers[i].taille), sizeof(int), 1, archive);
            fputc('\0', archive);
            compression_fichier(archive, liste_fichiers[i], alphabet);
        }
    }
    for (i = 0; i < 256; i++)
        if (alphabet[i] != NULL) libere(alphabet[i]);
    fclose(archive);
}