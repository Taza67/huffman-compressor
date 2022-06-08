#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "arbre_huffman.h"
#include "gestion_fichiers.h"

/* écrit le codage de huffman du fichier à compresser dans l'archive */
void ecrire_codage(FILE* fichier, FILE* archive, noeud* alphabet[256]);

/* compresse un fichier dans une archive déjà ouverte */
void compression_fichier(FILE *archive, file struct_fichier, noeud *alphabet[256]);

/* écrit récursivement une arborescence de fichiers et de dossiers dans l'archive */
void compression_arborescence(FILE *archive, noeud* alphabet[256], file * liste_fichiers, int nombre_fichiers);

/* compte le nombre total d'entrées de l'arborescence */
int compter_arborescence(file * liste_fichiers, int nombre_fichiers);

/* liste les sous-fichiers d'un dossier et les préfixe du chemin du dossier */
file * lister_sous_fichiers(char * nom_dossier, int * nombre_sous_fichiers);

/* compresse une liste de fichiers dans une archive */
void compression(file * liste_fichiers, int nombre_fichiers, char *nom_archive);

#endif