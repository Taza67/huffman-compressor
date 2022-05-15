#ifndef _GESTION_ERREURS_H_
#define _GESTION_ERREURS_H_

void viderBuffer();

/* Affiche l'aide du programme */
void usage(char *programme);

/* Vérifie la ligne de commande : option et nombre d'arguments */
int verifier_ligne_arguments(int argc, char **argv, int nombre_minimum);

#endif