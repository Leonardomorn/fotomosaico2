#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include "list.h"
#include <math.h>


void commentary_ignore(FILE *fpt);
void calculate_average_color(PPM* ppm);
void sub_photomosaic(int i, int j, PPM* tile, PPM** photomosaic );
void average_color_image(PPM *ppm, int i, int j, t_list* list, PPM** ppm_aux);
float color_distance(PPM* tile, PPM* sub_image);
void least_distance(t_list* l, PPM* sub_image, PPM** knot_aux);
void read_P6(char type[], FILE *fpt, t_list *l);
void read_P3(char type[], FILE * fpt, t_list* l);
int read_ppm(char *path_file, t_list *l);
int read_ppm_image(char *image_name, PPM** image_ptr);
void read_image_P6(char type[], FILE* fpt, PPM** image_ptr);
void read_image_P3(char type[],  FILE* fpt, PPM** image_ptr);
void write_image(PPM* ppm, char* output);
void cut_image(PPM** image_ptr, t_list tiles_list);
void average_color_image(PPM *ppm, int i, int j, t_list* list, PPM** ppm_aux);
void create_photomosaic(t_list* tiles_list, PPM* image_ptr, PPM** photomosaic_ptr);