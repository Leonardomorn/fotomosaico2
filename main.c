//programa feito por Leonardo da Silva Camargo
//GRR20203903 
//Gera fotomosaicos a partir de tiles e uma imagem de entrada. Tudo em formato PPM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "tiles.h"
#include "list.h"

int main (int argc, char* argv[])
{
    t_list tiles_list;
    initialize_list(&tiles_list);
    PPM* image_ptr = NULL;
    PPM* photomosaic = NULL;
    int tiles_num = 0;

    char* outputtest = "output.ppm";

    printf("calculating number of tiles\n");
    tiles_num = number_of_tiles_on_directory (argv, argc);
    printf("Number of tiles is: %d\n", tiles_num);

    read_tiles(tiles_num, argv, argc, &tiles_list);
    read_image(argv, argc, &image_ptr);
    cut_image(&image_ptr, tiles_list);
    create_photomosaic(&tiles_list, image_ptr, &photomosaic);
    write_image(photomosaic, outputtest);
    free_images(image_ptr, photomosaic);
    destroy_list(&tiles_list);

}