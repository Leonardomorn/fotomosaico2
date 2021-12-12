
#pragma once
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include "list.h"
#include "ppm.h"


int number_of_tiles_on_directory(char *argv[], int argc); /*return the number of tiles on the directory
                                                            if not especified by entry (-p), will be direcory 
                                                            tiles by default*/
void read_ppm_diretory(char* directory, t_list* tiles_list);
void read_tiles(int tiles_num, char *argv[], int argc, t_list* tiles_list);
void read_image(char* argv[], int argc, t_list** image_ptr);