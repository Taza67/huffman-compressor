#include <stdio.h>
#include <stdlib.h>
#include "gestion_erreurs.h"

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void usage(char* programme) {
    fprintf(stderr, "- Usage : %s <option> [arguments]\n", programme);
    fprintf(stderr, "  Options :\n");
    fprintf(stderr, "    -c <archive> <fichier|dossier> [...]  compresser un ou plusieurs fichiers\n");
    fprintf(stderr, "    -d <archive> [dossier_cible]          décompresser une archive\n");
    fprintf(stderr, "    -h                                    afficher cette aide\n");
}

int verifier_ligne_arguments(int argc, char **argv, int nombre_minimum) {
    if (argc < 2) {
        fprintf(stderr, "- Erreur -> fonction verifier_ligne_arguments : il manque une option !\n");
        usage(argv[0]);
        return 1;
    }
    if (argv[1][0] != '-') {
        fprintf(stderr, "- Erreur -> fonction verifier_ligne_arguments : l'option %s doit commencer par un tiret !\n", argv[1]);
        usage(argv[0]);
        return 1;
    }
    if (argv[1][1] != 'c' && argv[1][1] != 'd' && argv[1][1] != 'h') {
        fprintf(stderr, "- Erreur -> fonction verifier_ligne_arguments : option %s inconnue !\n", argv[1]);
        usage(argv[0]);
        return 1;
    }
    if (argv[1][1] == 'h') return 0;
    if (argc < nombre_minimum) {
        fprintf(stderr, "- Erreur -> fonction verifier_ligne_arguments : nombre d'arguments insuffisant !\n");
        usage(argv[0]);
        return 1;
    }
    return 0;
}