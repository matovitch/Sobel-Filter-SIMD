#ifndef __PGM_INTERFACE_H__
#define __PGM_INTERFACE_H__

#include <stdint.h>

static const uint16_t PGM_MAGIC = 0x3550;          //nombre magique
static const uint16_t BUFF_SIZE = 1 << 8;          //taille du tampon

/*Structure contenant l'image en niveaux de gris*/
struct greyscale_image {
    uint32_t width, height;     //lageur et hauteur
    uint8_t* pixels;            //pointeur vers les pixels
};

typedef struct greyscale_image greyscale_image;

/*Charge le fichier 'filename' dans l'image 'to_load'*/
void load_from_pgm(char* filename, greyscale_image* to_load);

/*Ecrit l'image 'to_write' dans le fichier 'filename'*/
void write_to_pgm(greyscale_image* to_write, char* filename);

#endif 
