#include <stdio.h>
#include <stdlib.h>
#include "gestion_erreurs.h"
#include "compression.h"
#include "decompression.h"

int main(int argc, char ** argv) {
    char * dossier_cible;
    if (argc < 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    switch (argv[1][1]) {
    case 'c':
        compression_fichier(argv[2], argv[3]);
        break;
    case 'd':
        dossier_cible = (argc == 4) ? argv[3] : ".";
        decompression_fichier(argv[2], dossier_cible);
        break;
    case 'h':
        usage(argv[0]);
        break;
    }
    exit(EXIT_SUCCESS);
}