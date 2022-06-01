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
    int longueur_chemin = strlen(nom_dossier_parent) + strlen(nom_fichier) + 2;
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

file * lister_fichiers(int taille_ligne, char ** ligne_arguments)  {
    int taille_liste_fichiers = taille_ligne - 3, i = 0;
    file * liste_fichiers = (file*)allocation_mem_init0(taille_liste_fichiers, sizeof(file));
    for (i = 3; i < taille_ligne; i++) {
        char type = 0;
        liste_fichiers[i - 3].nom = (char*)allocation_mem_init0(strlen(ligne_arguments[i]), sizeof(char));
        strcpy(liste_fichiers[i - 3].nom, ligne_arguments[i]);
        type = renvoyer_type(liste_fichiers[i - 3].nom);
        if (type != 'f' && type != 'd') {
            fprintf(stderr, "- Erreur fonction lister_fichiers(int taille_ligne, char ** ligne_arguments) : le fichier %s n'est ni un fichier, ni un dossier !\n", liste_fichiers[i - 3].nom);
            exit(EXIT_FAILURE);
        }
        liste_fichiers[i - 3].type = type;
        liste_fichiers[i - 3].taille = 0;
    }
    return liste_fichiers;
}

file * lister_fichiers_dossier(char * nom_dossier)  {
    DIR* rep = NULL;
    struct dirent* fichier = NULL;
    file * liste_fichiers = NULL;
    int nombre_fichiers = 0,
        i = 0;
    if ((rep = opendir(nom_dossier)) == NULL) {
        fprintf(stderr, "- Erreur -> fonction lister_fichiers_dossier(char * nom_dossier) : ouverture du dossier %s impossible !\n", nom_dossier);
        exit(EXIT_FAILURE);
    }
    while ((fichier = readdir(rep)) != NULL) {
        if (strcmp(fichier->d_name, ".") != 0 && strcmp(fichier->d_name, "..") != 0) {
            nombre_fichiers++;
        }
    }
    rewinddir(rep);
    liste_fichiers = (file*)allocation_mem_init0(nombre_fichiers, sizeof(file));
    while ((fichier = readdir(rep)) != NULL) {
        if (strcmp(fichier->d_name, ".") != 0 && strcmp(fichier->d_name, "..") != 0) {
            char * chemin = creer_chemin_fichier(nom_dossier, fichier->d_name);
            liste_fichiers[i].nom = (char*)allocation_mem_init0(strlen(fichier->d_name) + 1, sizeof(char));
            strcpy(liste_fichiers[i].nom, fichier->d_name);
            liste_fichiers[i].type = renvoyer_type(chemin);
            liste_fichiers[i].taille = 0;
            libere(chemin);
            i++;
        }
    }
    closedir(rep);
    return liste_fichiers;
}

int renvoyer_nombre_fichiers_dossier(char * nom_dossier) {
    DIR* rep = NULL;
    struct dirent* fichier = NULL;
    int nombre_fichiers = 0;
    if ((rep = opendir(nom_dossier)) == NULL) {
        fprintf(stderr, "- Erreur -> fonction renvoyer_nombre_fichiers_dossier(char * nom_dossier) : ouverture du dossier %s impossible !\n", nom_dossier);
        exit(EXIT_FAILURE);
    }
    while ((fichier = readdir(rep)) != NULL) {
        if (strcmp(fichier->d_name, ".") != 0 && strcmp(fichier->d_name, "..") != 0) {
            nombre_fichiers++;
        }
    }
    closedir(rep);
    return nombre_fichiers;
}