#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocation.h"
#include "arbre_huffman.h"
#include "gestion_fichiers.h"
#include "en_tete.h"

/* ******************************Version 0****************************** */

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

void ecrire_entete(file* liste_fichiers, FILE* archive, int nombre_fichiers, noeud* alphabet[256]) {
    int tab_occurence[256],
        nbr_char = 0,
        taille_fichier = 0,
        i = 0;
    noeud* arbre_huffman[256];
    for(i = 0;i < 256; i++) {
        alphabet[i] = NULL;
        tab_occurence[i] = 0;
        arbre_huffman[i] = NULL;
    }
    calculer_occurences_totales(liste_fichiers, nombre_fichiers, tab_occurence);
    creer_tous_noeuds(arbre_huffman, tab_occurence, &nbr_char, &taille_fichier);
    creer_noeud(arbre_huffman, nbr_char);
    creer_code(*arbre_huffman, 0, 0, alphabet);
    afficher_codes(alphabet);
    ecrire_entete_aux(archive, alphabet);  
}

void calculer_occurences_totales(file* liste_fichiers, int nombre_fichiers, int tab_occurence[256]) {
    int i = 0;
    for (i = 0; i < nombre_fichiers; i++) {
        if (liste_fichiers[i].type == 'f') {
            occurence(liste_fichiers[i].nom, tab_occurence);
        } else if (liste_fichiers[i].type == 'd') {
            int nombre_sous_fichiers = renvoyer_nombre_fichiers_dossier(liste_fichiers[i].nom);
            file * sous_fichiers = lister_fichiers_dossier(liste_fichiers[i].nom);
            int j = 0;
            for (j = 0; j < nombre_sous_fichiers; j++) {
                char * ancien_nom = sous_fichiers[j].nom;
                sous_fichiers[j].nom = creer_chemin_fichier(liste_fichiers[i].nom, ancien_nom);
                libere(ancien_nom);
            }
            calculer_occurences_totales(sous_fichiers, nombre_sous_fichiers, tab_occurence);
            for (j = 0; j < nombre_sous_fichiers; j++) libere(sous_fichiers[j].nom);
            libere(sous_fichiers);
        }
    }
}