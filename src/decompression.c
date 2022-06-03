#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "allocation.h"
#include "gestion_fichiers.h"
#include "en_tete.h"
#include "decompression.h"

/* ******************************Version 0****************************** */

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

/* ******************************Version 1****************************** */

void decompression_fichier(FILE *archive, char * nom_fichier, noeud* arbre_huffman[256]) {
    FILE *fichier = NULL;
    int taille_fichier = 0;
    char * name = NULL;
    name = renvoyer_nom_modifie(nom_fichier, 'f');
    if ((fichier = fopen(name, "w")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(FILE *archive, char *nom_fichier) : ouverture du fichier %s impossible !\n", name);
        exit(EXIT_FAILURE);
    }
    if (archive == NULL) {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(FILE *archive, char *nom_fichier) : archive = NULL !\n");
        exit(EXIT_FAILURE);
    }
    if (fread(&(taille_fichier), sizeof(int), 1, archive) != 1) {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(FILE *archive, char * nom_fichier, noeud* arbre_huffman[256]) : récupération du nombre de fichiers échouée !\n");
        exit(EXIT_FAILURE);
    }
    if (fgetc(archive) != '\0') {
        fprintf(stderr, "- Erreur -> fonction decompression_fichier(FILE *archive, char * nom_fichier, noeud* arbre_huffman[256]) : séparateur non trouvé, fichier erroné !\n");
        exit(EXIT_FAILURE);
    }
    recuperer_contenu(archive, fichier, arbre_huffman, taille_fichier);
    fclose(fichier);
}

/* ******************************Version 2****************************** */

/* crée récursivement les dossiers parents d'un chemin */
void creer_dossier_parent(char *chemin) {
    int i = 0, taille = strlen(chemin);
    char *copie = (char*)allocation_mem_init0(taille + 1, sizeof(char));
    strcpy(copie, chemin);
    for (i = 1; i < taille; i++) {
        if (copie[i] == '/') {
            copie[i] = '\0';
            mkdir(copie, 0777);
            copie[i] = '/';
        }
    }
    libere(copie);
}

char * recuperer_nom_fichier(FILE* archive) {
    int taille_nom = 10, j = 0, caractere = 0;
    char * nom_fichier = (char*)allocation_mem_init0(10, sizeof(char));
    for (j = 0; (caractere = fgetc(archive)) != '\0' && caractere != EOF; j++) {
        if (j + 1 >= taille_nom) {
            taille_nom += 10;
            nom_fichier = (char *)reallocation_mem(nom_fichier, taille_nom, sizeof(char));
        }
        nom_fichier[j] = caractere;
    }
    nom_fichier[j] = '\0';
    return nom_fichier;
}

void decompression(char *nom_archive, char *dossier_cible) {
    FILE *archive = NULL;
    int nombre_fichiers = 0,
        type = 0, sep = 0, i = 0,
        occurence[256],
        nbr_char = 0,
        taille_fichier = 0;
    noeud *alphabet[256],
        *arbre_huffman[256];
    if (strcmp(dossier_cible, ".") != 0 && verifier_dossier(dossier_cible) != 1)
        mkdir(dossier_cible, 0777);
    for (i = 0; i < 256; i++) {
        occurence[i] = 0;
        alphabet[i] = NULL;
        arbre_huffman[i] = NULL;
    }
    if ((archive = fopen(nom_archive, "rb")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction decompression(char *nom_archive) : ouverture de l'archive %s impossible !\n", nom_archive);
        exit(EXIT_FAILURE);
    }
    recuperer_entete(archive, occurence);
    creer_tous_noeuds(arbre_huffman, occurence, &nbr_char, &taille_fichier);
    creer_noeud(arbre_huffman, nbr_char);
    creer_code(*arbre_huffman, 0, 0, alphabet);
    if (fread(&(nombre_fichiers), sizeof(int), 1, archive) != 1) {
        fprintf(stderr, "- Erreur -> fonction decompression(char *nom_archive) : récupération du nombre de fichiers échouée !\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < nombre_fichiers; i++) {
        char *nom_fichier = NULL;
        if (((type = fgetc(archive)) != 'f' && type != 'd') || type == EOF || (sep = fgetc(archive)) != '\0') {
            fprintf(stderr, "- Erreur -> fonction decompression(char *nom_archive) : récupération du type échouée à l'indice %d !\n", i);
            exit(EXIT_FAILURE);
        }
        nom_fichier = recuperer_nom_fichier(archive);
        nom_fichier = creer_chemin_fichier(dossier_cible, nom_fichier);
        if (type == 'f') {
            creer_dossier_parent(nom_fichier);
            decompression_fichier(archive, nom_fichier, arbre_huffman);
        } else if (type == 'd') {
            if (verifier_dossier(nom_fichier) != 1) mkdir(nom_fichier, 0777);
        }
        libere(nom_fichier);
    }
    for (i = 0; i < 256; i++)
        if (alphabet[i] != NULL) libere(alphabet[i]);
    fclose(archive);
}