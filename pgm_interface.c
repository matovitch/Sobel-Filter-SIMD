#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pgm_interface.h"

void load_from_pgm(char* filename, greyscale_image* to_load) {
    char buff[BUFF_SIZE];               //allocation d'un tampon
    uint8_t count;
    uint32_t offset = 0;                //curseur d'écriture
    FILE* file = fopen(filename, "r");  //ouverture du fichier

    if (file == NULL) {
        printf("Echec de l'ouverture du fichier en lecture\n");
        return;
    }

    if(fgets(buff, sizeof buff, file) == NULL
       || *(uint16_t*)buff != PGM_MAGIC) {
        printf("Le fichier n'est pas au format PGMB\n");
        return;
    }

    if (fgets(buff, sizeof buff, file) == NULL
        || sscanf(buff, "%d %d",
                  &(to_load->width),
                  &(to_load->height))  == EOF) {
        printf("L'entête du fichier est mal formée.\n");
        return;
    }

    //allocation de l'image
    to_load->pixels = (uint8_t*)malloc(sizeof(uint8_t) *
                                       to_load->width *
                                       to_load->height);
    if (to_load == NULL) {
        printf("Echec de l'allocation de l'image.\n");
        return;
    }

    fgets(buff, sizeof buff, file); //passe la ligne '255\n'
    
    //copie les pixels en mémoire
    fread(to_load->pixels, sizeof(uint8_t),  
          to_load->width * to_load->height, file);
    
    fclose(file);   //fermeture du fichier
}

void write_to_pgm(greyscale_image* to_write, char* filename) {
    FILE* file = fopen(filename, "w");  //ouverture du fichier

    if (file == NULL) {
        printf("Echec de l'ouverture du fichier en écriture\n");
        return;
    }

    //écrit le nombre magique
    fwrite(&PGM_MAGIC, sizeof(uint8_t), sizeof PGM_MAGIC, file);

    //puis l'entête
    fprintf(file, "\n%d %d\n%d\n",to_write->width,
                                to_write->height,
                                1 << CHAR_BIT - 1);

    //et les données
    fwrite(to_write->pixels, sizeof(uint8_t),
                             to_write->width * to_write->height,
                             file);

    fclose(file);   //fermeture du fichier
}
