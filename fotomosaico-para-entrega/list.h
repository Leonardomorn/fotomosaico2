#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char red,green,blue;
} Pixel;


typedef struct PPM  {
    char type[3];
    int width, height;
    int max;
    Pixel average_color;
    float color_distance;
    Pixel **matriz_pixel;    
    struct PPM *next_knot;
    struct PPM *prev_knot;

} PPM;  

typedef struct t_list
{
    struct PPM *first;
}t_list;


int initialize_list( t_list *l);
int list_is_empty (t_list *l);
int add_empty_list (t_list *l, PPM *knot);
int append(t_list *l, PPM *knot);
void remove_list(t_list *l);
void destroy_list(t_list *l);