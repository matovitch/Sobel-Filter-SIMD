#include <stdio.h>

#include "pgm_interface.h"

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Erreur : Mauvais nombre d'argument.\n");
        return -1;
    }

    greyscale_image img;

    load_from_pgm(argv[1], &img);
    write_to_pgm(&img, argv[2]);

    return 0;
}