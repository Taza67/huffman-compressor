#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "allocation.h"
#include "gestion_fichiers.h"

int verifier_dossier(char * nom_fichier) {
    DIR *is_dossier = NULL;
    int retour = 0;
    if ((is_dossier = opendir(nom_fichier)) != NULL) {
        closedir(is_dossier);
        retour = 1;
    }
    return retour;
}

int verifier_fichier(char * nom_fichier) {
    FILE *is_fichier = NULL;
    int retour = 0;
    if ((is_fichier = fopen(nom_fichier, "r")) != NULL) {
        fclose(is_fichier);
        retour = 1;
    }
    return retour;
}

char renvoyer_type(char *nom_fichier) {
    char type = 'e';
    if (verifier_dossier(nom_fichier) == 1) type = 'd';
    else if (verifier_fichier(nom_fichier) == 1) type = 'f';
    return type;
}

char * creer_chemin_fichier(char *nom_dossier_parent, char *nom_fichier) {
    int longueur_chemin = strlen(nom_dossier_parent) + strlen(nom_fichier) + 1;
    char *chemin = (char*)allocation_mem_init0(longueur_chemin, sizeof(char));
    strcpy(chemin, nom_dossier_parent);
    strcat(chemin, "/");
    strcat(chemin, nom_fichier);
    return chemin;
}

char * renvoyer_nom_modifie(char * nom, char type) {
    int i = 0, taille = strlen(nom) + 2, stop = 0;
    char * new_name = (char*)allocation_mem_init0(taille, sizeof(char));
    strcpy(new_name, nom);
    for (i = 0; stop != 1; i++) {
        int verif = (type == 'd') ? verifier_dossier(new_name) : verifier_fichier(new_name);          
        if (verif == 1) {
            new_name[taille - 2] = i + '0';
            new_name[taille - 1] = '\0';
        } else {
            stop = 1;
        }
    }
    return new_name;
}