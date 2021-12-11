#include "ppm.h"



void commentary_ignore(FILE *fpt)
{
    char c;
    
    c = getc(fpt);
    while ((c =='#') || (c == '\n'))
    {
        while (c != '\n')
        {
            c=getc(fpt);
        }
        c=getc(fpt);
    }
    ungetc(c,fpt);

}

void calculate_average_color(PPM* ppm)
{
     long unsigned int r=0;
     long unsigned int g=0;
     long unsigned int b=0;

     int number_of_pixels = ppm->height * ppm->width;
     
     for (int i = 0; i<ppm->height; i++)
     {
         for (int j = 0; j<ppm->width; j++)
         {
             r = r + ppm->matriz_pixel[i][j].red;
             g = g + ppm->matriz_pixel[i][j].green;
             b = b + ppm->matriz_pixel[i][j].blue;
         }
     }

     r = r / number_of_pixels; g = g/ number_of_pixels; b = b/ number_of_pixels;

    ppm->average_color.red   = r;
    ppm->average_color.green = g;
    ppm->average_color.blue  = b;

    printf("the average color is %ld %ld %ld \n ", r, g ,b);
       
}

void read_P6(char type[], FILE *fpt, t_list *l)
{
    printf("entrou em read_P6");
	PPM* ppm; 
	ppm = malloc (sizeof(PPM));

	strncpy(ppm->type, type, 3);
	commentary_ignore(fpt);

	fscanf(fpt, " %d %d ", &(ppm->width), &(ppm->height));
	commentary_ignore(fpt);

	fscanf(fpt, "%d ", &(ppm->max));
	commentary_ignore(fpt);

	ppm->matriz_pixel = malloc(ppm->height * sizeof(Pixel));
	for(int i = 0; i<ppm->height; i++)
	{
		ppm->matriz_pixel[i] = malloc (ppm->width * sizeof (Pixel));
	}

	for(int i = 0; i<ppm->height; i++)
	{
		for(int j = 0; j<ppm->width; j++)
		{
			fscanf(fpt, "%c%c%c",
			 &(ppm->matriz_pixel[i][j].red),
			  &(ppm->matriz_pixel[i][j].green),
			   &(ppm->matriz_pixel[i][j].blue));
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

          
    printf("saiu de read_p6");
}

int read_ppm(char *path_file, t_list *l)
{
   char type[3];   
   FILE *fpt = fopen(path_file, "r");


     if (!fpt)
     {
          fprintf(stderr , "unable to open %s \n", path_file);
          return 0;
     }
     fscanf(fpt, "%s ", type);
     fprintf(stderr, "type is %s", type);
     if(strcmp(type, "P6") == 0 ) /*verifica se é P6*/
     {
         read_P6(type, fpt, l);
/*            printf("%s\n", ppm->type);
          printf("%d %d\n", ppm->lar, ppm->alt);
          printf("%d\n", ppm->max);
          for(i=0; i<(ppm->alt * ppm->lar); i++)
          {
               printf("%c%c%c", ppm->matriz_pixel[i].red, ppm->matriz_pixel[i].green, ppm->matriz_pixel[i].blue);
          }
  */
     }
          else if (strcmp(type, "P3") == 0 ) /*Verifica se é P3*/
          {
			  return 0;            
          }
               else /*a pastilha não é valida*/
               {
                    exit(0);
               }



     fclose(fpt);
     return 0;
}