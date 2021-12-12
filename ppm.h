#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include "list.h"
#include <math.h>


void commentary_ignore(FILE *fpt);
void calculate_average_color(PPM* ppm);
void read_P6(char type[], FILE *fpt, t_list *l);
void read_P3(char type[], FILE * fpt, t_list* l);
int read_ppm(char *path_file, t_list *l);
int read_ppm_image(char *image_name, PPM** image_ptr);
void read_image_P6(char *type [], FILE* fpt, PPM** image_ptr);
void read_image_P3(char* type[],  FILE* fpt, PPM** image_ptr);
