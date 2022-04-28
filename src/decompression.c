#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocation.h"
#include "gestion_fichiers.h"
#include "en_tete.h"
#include "decompression.h"

void recuperer_contenu(FILE* archive, FILE* fichier, noeud* arbre_huffman[], int taille_fichier) {
    noeud * feuille_caractere = NULL;
    int codage = 0;
    int paquet = 0, taille_paquet = 0,
        ajout = taille_fichier;
    if (archive == NULL) {
        fprintf(stderr, "- Erreur -> fonction recuperer_contenu(FILE* archive, FILE* fichier, noeud* arbre_huffman[256], int taille_fichier) : archive = NULL !\n");
        exit(EXIT_FAILURE);
    }
    if (fichier == NULL) {
        fprintf(stderr, "- Erreur -> fonction recuperer_contenu(FILE* archive, FILE* fichier, noeud* arbre_huffman[256], int taille_fichier) : fichier = NULL !\n");
        exit(EXIT_FAILURE);
    }
    while((codage = fgetc(archive)) != EOF && ajout > 0) {
        paquet = paquet << 8;
        paquet = paquet | codage;
        taille_paquet += 8;
        while ((feuille_caractere = recuperer_feuille(*arbre_huffman, paquet, taille_paquet, 0)) != NULL && ajout > 0) {
            fputc(feuille_caractere->initial, fichier);
            taille_paquet -= feuille_caractere->bits;
            ajout--;
        }
    }
}

noeud * recuperer_feuille(noeud *racine, int paquet, int taille_paquet, int profondeur) {
    int bit = (paquet >> (taille_paquet - profondeur - 1)) & 1;
    if (taille_paquet < profondeur) return NULL;
    if (racine->gauche == NULL && racine->droit == NULL) return racine;
    if (racine->gauche != NULL && bit == 0)
        return recuperer_feuille(racine->gauche, paquet, taille_paquet, profondeur + 1);
    if (racine->droit != NULL && bit == 1)
        return recuperer_feuille(racine->droit, paquet, taille_paquet, profondeur + 1);
    return NULL;
}

void decompression_fichier(char * nom_archive, char *dossier_cible) {
    FILE *fichier = NULL, *archive = NULL;
    int taille_nom = 10 , j = 0;
    char *nom_fichier = (char*)allocation_mem_init0(10, sizeof(char)), caractere, *name = NULL;
    int occurence[256],
        nbr_char = 0,
        taille_fichier = 0,
        i = 0;
    noeud *alphabet[256],
        *arbre_huffman[256];
    for (i = 0; i < 256; i++) {
        occurence[i] = 0;
        alphabet[i] = NULL;
        arbre_huffman[i] = NULL;
    }
    if ((archive = fopen(nom_archive, "rb")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(char* nom_archive, char* nom_fichier) : ouverture de l'archive %s impossible !\n", nom_archive);
        exit(EXIT_FAILURE);
    }
    for (j = 0; (caractere = fgetc(archive)) != '\0' && caractere != EOF; j++) {
        if (j + 1 > taille_nom) {
            taille_nom += 10;
            nom_fichier = (char *)reallocation_mem(nom_fichier, taille_nom, sizeof(char));
        }
        nom_fichier[j] = caractere;
    }
    nom_fichier[j] = '\0';
    nom_fichier = creer_chemin_fichier(dossier_cible, nom_fichier);
    name = renvoyer_nom_modifie(nom_fichier, 'f');
    if ((fichier = fopen(name, "w")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(char* nom_archive, char* nom_fichier) : ouverture du fichier %s impossible !\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    recuperer_entete(archive, occurence);
    creer_tous_noeuds(arbre_huffman, occurence, &nbr_char, &taille_fichier);
    creer_noeud(arbre_huffman, nbr_char);
    creer_code(*arbre_huffman, 0, 0, alphabet);
    recuperer_contenu(archive, fichier, arbre_huffman, taille_fichier);
    for (i = 0; i < 256; i++)
        if (alphabet[i] != NULL) libere(alphabet[i]);
    fclose(fichier);
    fclose(archive);
}