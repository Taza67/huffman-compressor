#ifndef _GESTION_FICHIERS_H_
#define _GESTION_FICHIERS_H_

/* Vérifie si un dossier existe */
int verifier_dossier(char * nom_fichier);

/* Vérifie si un fichier existe */
int verifier_fichier(char * nom_fichier);

/* Renvoie le type d'un fichier */
char renvoyer_type(char *nom_fichier);

/* Rajoute le chemin du répertoire parent au chemin d'un sous-fichier */
char * creer_chemin_fichier(char *nom_dossier_parent, char *nom_fichier);

/* Modifie le nom d'un fichier si le dernier est déjà attribué */
char * renvoyer_nom_modifie(char * nom, char type);

#endif