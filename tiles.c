#include "tiles.h"

int number_of_tiles_on_directory(char *argv[], int argc)
{
    char* path = NULL;
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-p") == 0)
			path = argv[i+1]; 
	}
	if(path == NULL)
	{
		path = "tiles";
        printf("the path is %s\n", path);

	}

	int tiles_number = 0;
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			if(dir->d_type == DT_REG)
			{
				tiles_number++;
			}
		}
	}
	closedir(d);
	return tiles_number;
}

void read_ppm_diretory(char* directory, t_list* tiles_list){
	printf("entrou em read ppm diretory\n");

     DIR *dirstream;
     struct dirent *direntry;
     char buffer[100];

     dirstream = opendir (directory);
     direntry = readdir (dirstream);


    while (direntry != NULL) {
          if (direntry->d_type == DT_REG) {
               //printf ("Nome: %s\n", direntry->d_name);

               strcat (buffer, directory);
               strcat (buffer, direntry->d_name);

               read_ppm (buffer, tiles_list);

               memset (buffer, 0, sizeof (buffer));
          }
          direntry = readdir (dirstream);
    }
	printf("saiu de read ppm diretory\n");
    (void) closedir (dirstream);
}



void read_tiles(int tiles_num, char *argv[], int argc, t_list* tiles_list)
{
	printf("entrou em read_tiles\n");
    char* path = NULL;
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-p") == 0)
			path = argv[i+1]; 
	}
	if(path == NULL)
	{
		path = "tiles";
        printf("the path is %s\n", path);

	}
	read_ppm_diretory(path, tiles_list);
	printf("saiu de read tiles\n");

}

