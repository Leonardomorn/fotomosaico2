#include "ppm.h"

int sucesso = 0;

void commentary_ignore(FILE *fpt)
{
    char c;

    c = getc(fpt);
    while ((c == '#') || (c == '\n'))
    {
        while (c != '\n')
        {
            c = getc(fpt);
        }
        c = getc(fpt);
    }
    ungetc(c, fpt);
}

void calculate_average_color(PPM *ppm)
{
    long unsigned int r = 0;
    long unsigned int g = 0;
    long unsigned int b = 0;

    int number_of_pixels = ppm->height * ppm->width;

    for (int i = 0; i < ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            r = r + ppm->matriz_pixel[i][j].red;
            g = g + ppm->matriz_pixel[i][j].green;
            b = b + ppm->matriz_pixel[i][j].blue;
        }
    }

    r = r / number_of_pixels;
    g = g / number_of_pixels;
    b = b / number_of_pixels;

    ppm->average_color.red = r;
    ppm->average_color.green = g;
    ppm->average_color.blue = b;

    // printf("the average color is %ld %ld %ld \n ", r, g, b);
}

void read_P6(char type[], FILE *fpt, t_list *l)
{
    PPM *ppm;
    ppm = malloc(sizeof(PPM));

    strncpy(ppm->type, type, 3);

    printf("guardou o tipo P\n");

    commentary_ignore(fpt);

    printf("ignorou comentário \n");

    fscanf(fpt, "%d %d\n", &(ppm->width), &(ppm->height));

    printf("LARGURA é %d", ppm->width );

    fscanf(fpt, "%d\n", &(ppm->max));

    ppm->matriz_pixel = (Pixel**)malloc(ppm->height * sizeof(Pixel*));
    if(!ppm->matriz_pixel){ 
        fprintf(stderr, "não alocou memória");
        exit(0);
    }
    for (int i = 0; i < ppm->height; i++)
    {
        ppm->matriz_pixel[i] = (Pixel*) malloc(ppm->width * sizeof(Pixel));
        if(!ppm->matriz_pixel[i]){
            fprintf(stderr, "não alocou memória");
        }
    }

    for (int i = 0; i < ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            fscanf(fpt, "%c%c%c",
                   &(ppm->matriz_pixel[i][j].red),
                   &(ppm->matriz_pixel[i][j].green),
                   &(ppm->matriz_pixel[i][j].blue));
        }
    }
    sucesso++;
    printf("\n NÚMERO DE LIDOS: %d \n", sucesso);
    calculate_average_color(ppm);

    if (list_is_empty(l))
    {
        add_empty_list(l, ppm);
    }
    else
    {
        append(l, ppm);
    }

}

void read_P3(char type[], FILE * fpt, t_list* l)
{
    PPM *ppm;
    ppm = malloc(sizeof(PPM));
    int r = 0; int b = 0; int g = 0;

    strncpy(ppm->type, type, 3);

    printf("guardou o tipo P\n");

    commentary_ignore(fpt);

    printf("ignorou comentário \n");

    fscanf(fpt, "%d %d\n", &(ppm->width), &(ppm->height));

    printf("LARGURA é %d", ppm->width );

    fscanf(fpt, "%d\n", &(ppm->max));

    ppm->matriz_pixel = (Pixel**)malloc(ppm->height * sizeof(Pixel*));
    if(!ppm->matriz_pixel){ 
        fprintf(stderr, "não alocou memória");
        exit(0);
    }
    for (int i = 0; i < ppm->height; i++)
    {
        ppm->matriz_pixel[i] = (Pixel*) malloc(ppm->width * sizeof(Pixel));
        if(!ppm->matriz_pixel[i]){
            fprintf(stderr, "não alocou memória");
        }
    }

    for (int i = 0; i < ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            fscanf(fpt, "%d%d%d", &r, &g, &b );
            ppm->matriz_pixel[i][j].red   = r;
            ppm->matriz_pixel[i][j].green = g;
            ppm->matriz_pixel[i][j].blue  = b;
        }
    }

    calculate_average_color(ppm);

    if (list_is_empty(l))
    {
        add_empty_list(l, ppm);
    }
    else
    {
        append(l, ppm);
    }

}

int read_ppm(char *path_file, t_list *l)
{
    char type[3];
    FILE *fpt = fopen(path_file, "r");

    if (!fpt)
    {
        fprintf(stderr, "unable to open %s \n", path_file);
        exit(0);
    }
    printf("opening %s\n", path_file);
    fscanf(fpt, "%s ", type);
    fprintf(stderr, "type is %s\n", type);
    if (strcmp(type, "P6") == 0) /*verifica se é P6*/
    {
        read_P6(type, fpt, l);

    }
    else if (strcmp(type, "P3") == 0) /*Verifica se é P3*/
    {
        read_P3(type, fpt, l);
    }
    else /*a pastilha não é valida*/
    {
        exit(0);
    }


    fclose(fpt);
    return 1;
}

int read_ppm_image(char *image_name, PPM** image_ptr)
{
     char type[3];   
     FILE *fpt = fopen(image_name, "r");


     if (!fpt)
     {
          fprintf(stderr , "unable to open %s \n", image_name);
          return 0;
     }
     fscanf(fpt, "%s ", type);
     if(strcmp(type, "P6") == 0 ) /*verifica se é P6*/
     {
        read_image_P6(type, fpt, image_ptr);
        return 1;

     }
          else if (strcmp(type, "P3") == 0 ) /*Verifica se é P3*/
          {
              read_image_P3(type, fpt, image_ptr);
              return 1;
          }
               else /*a imagem não é valida*/
               {
                    exit(0);
               }



     fclose(fpt);
     return 0;
}

void read_image_P6(char type[], FILE* fpt, PPM** image_ptr)
{
    PPM* ppm;
    ppm = malloc(sizeof(PPM));   
    if(ppm == NULL)
    {
        fprintf(stderr, "allocate ppm error\n");
    }

    strncpy(ppm->type, type, 3);
    commentary_ignore(fpt);
    
    fscanf(fpt, " %d %d ", &(ppm->width), &(ppm->height));
    
    fscanf(fpt, "%d ", &(ppm->max)); 

    ppm->matriz_pixel = (Pixel**)malloc(ppm->height * sizeof(Pixel*));
    if(!ppm->matriz_pixel){ 
        fprintf(stderr, "memory alocate error");
        exit(0);
    }
    for (int i = 0; i < ppm->height; i++)
    {
        ppm->matriz_pixel[i] = (Pixel*) malloc(ppm->width * sizeof(Pixel));
        if(!ppm->matriz_pixel[i]){
            fprintf(stderr, "memory alocate error");
        }
    }
             
    for(int i=0; i<ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            fscanf(fpt,"%c%c%c", 
             &(ppm->matriz_pixel[i][j].red) ,
              &(ppm->matriz_pixel[i][j].green),
               &(ppm->matriz_pixel[i][j].blue) );
        }
        

    }              
    

    *image_ptr = ppm;
    
}

void read_image_P3(char type[],  FILE* fpt, PPM** image_ptr)
{
    PPM* ppm;
    ppm = malloc(sizeof(PPM));
    int r = 0; int g = 0; int b=0;   
    if(ppm == NULL)
    {
        fprintf(stderr, "allocate ppm error\n");
    }

    strncpy(ppm->type, type, 3);
    commentary_ignore(fpt);
    
    fscanf(fpt, " %d %d ", &(ppm->width), &(ppm->height));
    
    fscanf(fpt, "%d ", &(ppm->max)); 

    ppm->matriz_pixel = (Pixel**)malloc(ppm->height * sizeof(Pixel*));
    if(!ppm->matriz_pixel){ 
        fprintf(stderr, "memory alocate error");
        exit(0);
    }
    for (int i = 0; i < ppm->height; i++)
    {
        ppm->matriz_pixel[i] = (Pixel*) malloc(ppm->width * sizeof(Pixel));
        if(!ppm->matriz_pixel[i]){
            fprintf(stderr, "memory alocate error");
        }
    }
             
    for(int i=0; i<ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            fscanf(fpt,"%d%d%d", &r, &g, &b);
            ppm->matriz_pixel[i][j].red   = r;
            ppm->matriz_pixel[i][j].green = g;
            ppm->matriz_pixel[i][j].blue  = b;
        }
        

    }              
    

    *image_ptr = ppm;    
}

void write_image(PPM* ppm, char* output)
{
    FILE *file;
    file = fopen(output, "w");
    if (!file)
    {
        printf("Erro ao criar arquivo.\n");
        exit(1);
    }

    fprintf(file, "%s\n", ppm->type);
    fprintf(file, "%d %d\n", ppm->width, ppm->height);
    fprintf(file, "%d\n", ppm->max);


    for (int i = 0; i < ppm->height; i++)
    {
        for (int j = 0; j < ppm->width; j++)
        {
            if(strcmp(ppm->type, "P3") == 0)
            {
                fprintf(file,"%d %d %d ", ppm->matriz_pixel[i][j].red, ppm->matriz_pixel[i][j].green, ppm->matriz_pixel[i][j].blue);
            }
                else
                {
                    fprintf(file, "%c%c%c", ppm->matriz_pixel[i][j].red, ppm->matriz_pixel[i][j].green, ppm->matriz_pixel[i][j].blue);
                }
        }
        
    }
    
} 

void cut_image(PPM** image_ptr, t_list tiles_list)
{
    int new_width = 0; int new_height = 0; int tiles_width =0; int tiles_height=0; 
    PPM* new_image = malloc(sizeof(PPM));

    tiles_width = tiles_list.first->width;
    tiles_height = tiles_list.first->height;

    new_width = floor((*image_ptr)->width / tiles_width) * tiles_width;
    new_height= floor((*image_ptr)->height / tiles_height) * tiles_height;

     
    strncpy(new_image->type, (*image_ptr)->type, 3);
    new_image->width = new_width;
    new_image->height = new_height;
    new_image->max = (*image_ptr)->max;


    new_image->matriz_pixel = (Pixel**)malloc(new_image->height * sizeof(Pixel*));
    if(!new_image->matriz_pixel){ 
        fprintf(stderr, "memory alocate error");
        exit(0);
    }
    for (int i = 0; i < new_image->height; i++)
    {
        new_image->matriz_pixel[i] = (Pixel*) malloc(new_image->width * sizeof(Pixel));
        if(!new_image->matriz_pixel[i]){
            fprintf(stderr, "memory alocate error");
        }
    }


    for (int i = 0; i < new_image->height; i++)
    {
        for (int j = 0; j < new_image->width; j++)
        {
            new_image->matriz_pixel[i][j] = (*image_ptr)->matriz_pixel[i][j];
        }
        
    }

    for (int i = 0; i < (*image_ptr)->height; i++)
    {
        free ((*image_ptr)->matriz_pixel[i]);
    }
    
    free(*image_ptr);
    *image_ptr = new_image;

}