#include <stdio.h>
#include <stdlib.h>
#include "allocation.h"
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

int total_occurence_fichier(char *nom_fichier) {
    int total_caracteres = 0;
    FILE *fichier = NULL;
    if ((fichier = fopen(nom_fichier, "r")) == NULL) {
        fprintf(stderr, "- Erreur -> fonction total_occurence_fichier(char *nom_fichier) : ouverture du fichier %s impossible !\n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        while (fgetc(fichier) != EOF) total_caracteres++;
    }
    fclose(fichier);
    return total_caracteres;
}

noeud * creer_feuille(int* tab, int index) {
    noeud* no = (noeud*)allocation_mem_init0(1, sizeof(noeud));
    no->initial = index;
    no->occurence = tab[index];
    return no;
}

void creer_tous_noeuds(noeud *arbre_huffman[], int occurence[256], int *nbr_char, int *taille_fichier) {
    int i = 0,
        local_nbr_char = 0,
        local_taille_fichier = 0;
    for (; i < 256; i++) {
        if (occurence[i] != 0) {
            arbre_huffman[i] = creer_feuille(occurence, i);
            local_nbr_char++;
            local_taille_fichier += occurence[i];
        }
    }
    *nbr_char = local_nbr_char;
    *taille_fichier = local_taille_fichier;
}

int chercher2petits(noeud * arbre_huffman[], int * first, int * second) {
    int i;
    *first = *second = -1;
    for (i = 0; i < 256; i++) {
        if (arbre_huffman[i] != NULL) {
            if (*first == -1) *first = i;
            else if (*second == -1) *second = i;
            else if (arbre_huffman[i]->occurence < arbre_huffman[*first]->occurence) {
                *first = i;
            } else if (arbre_huffman[i]->occurence <= arbre_huffman[*second]->occurence)
                *second = i;
        }
    }
    return (*first != -1 && *second != -1) ? 1 : 0;
}

void creer_noeud(noeud * arbre_huffman[], int taille) {
    int t = taille, new_occurence, first, second;
    noeud * tmp = NULL;
    while (t > 1) {
        chercher2petits(arbre_huffman, &first, &second);
        tmp = arbre_huffman[first];
        arbre_huffman[first] = (noeud*)allocation_mem_init0(1, sizeof(noeud));
        new_occurence = tmp->occurence + arbre_huffman[second]->occurence;
        arbre_huffman[first]->occurence = new_occurence;
        arbre_huffman[first]->gauche = tmp;
        arbre_huffman[first]->droit = arbre_huffman[second];
        arbre_huffman[second] = NULL;
        t--;
    }
    if (taille > 1) 
        *arbre_huffman = arbre_huffman[first];
}

void creer_code(noeud* element, int code, int profondeur, noeud* alphabet[256]) {
    if (element == NULL) return;
    if (element->droit == NULL && element->gauche == NULL) {
        element->bits = profondeur;
        element->code = code;
        alphabet[(int)element->initial] = element;
    } else {
        profondeur++;
        if (element->droit != NULL) {
            int new_code = (code << 1) + 1;
            creer_code(element->droit, new_code, profondeur, alphabet);
        }
        if (element->gauche != NULL) {
            int new_code = (code << 1);
            creer_code(element->gauche, new_code, profondeur, alphabet);
        }
    }
}

void affichage_code(int nbr_bits, int codage) {
    int * binaire = (int*)allocation_mem_init0(nbr_bits, sizeof(int));
    int i, *p;
    for (p = binaire; codage > 0; p++) {
        *p = codage % 2;
        codage = codage / 2;
    }
    for (i = nbr_bits - 1; i >= 0; i--) printf("%d", binaire[i]);
    printf("\n");
    free(binaire);
}

int calculer_profondeur_arbre(noeud* a) {
    int hauteur_max = 1;
    if (a == NULL) return 0;
    if (a->gauche != NULL) {
        int tmp = 1;
        tmp += calculer_profondeur_arbre(a->gauche);
        if (tmp > hauteur_max) hauteur_max = tmp;
    }
    if (a->droit != NULL) {
        int tmp = 1;
        tmp += calculer_profondeur_arbre(a->droit);
        if (tmp > hauteur_max) hauteur_max = tmp;
    }
    return hauteur_max;
}

void afficher_arbre_aux(noeud *a, int prof) {
    int i;
    for (i = 0; i < prof; printf("|"), i++ );
    printf( "%c -> ", a->initial);
    affichage_code(a->bits, a->code);
    if (a->gauche != NULL) afficher_arbre_aux(a->gauche, prof + 1);
    if (a->droit != NULL) afficher_arbre_aux( a->droit, prof + 1);
}

void afficher_arbre(noeud *a ) {
    afficher_arbre_aux(a, 0);
}