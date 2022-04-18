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
    fprintf(stderr, "- Usage : %s <option> [...]\n", programme);
}