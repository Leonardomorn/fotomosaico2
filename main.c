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
    PPM* image_ptr_new;
    int tiles_num = 0;

    printf("calculating number of tiles\n");
    tiles_num = number_of_tiles_on_directory (argv, argc);
    printf("Number of tiles is: %d\n", tiles_num);

    read_tiles(tiles_num, argv, argc, &tiles_list);


}