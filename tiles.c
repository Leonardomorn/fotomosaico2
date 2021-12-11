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
     char buffer[1024];

	 for (int i = 0; i < 1024; i++)
	 {
		buffer[i] = '\0';
	 }
	 

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
    char* def_dir = "tiles";
    char* changed_dir = NULL;
    int size = 0;

    for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-p") == 0)
        {
            if(argv[i+1] == NULL)
            {
                fprintf(stderr, "No argument found for -p!\n");
                exit(1);
            }
            else
            {
                size = strlen(argv[i + 1]);
                changed_dir = (char*)malloc((size + 2) * sizeof(char));
                if(!changed_dir)
                {
                    perror("Insufficient memory");
                    exit(1);
                }
                for(int j = 0; j < size; j++)
                    changed_dir[j] = argv[i + 1][j];
                changed_dir[size] = '/';
                changed_dir[size + 1] = '\0';
            }
        }
	}

    if(changed_dir == NULL)
    {
        size = strlen(def_dir);
        changed_dir = (char*)malloc((size + 2) * sizeof(char));
        if(!changed_dir)
        {
            perror("Insufficient memory");
            exit(1);
        }
        for(int k = 0; k < size; k++)
            changed_dir[k] = def_dir[k];
        changed_dir[size] = '/';
        changed_dir[size + 1] = '\0';
    }

    printf("%s\n", changed_dir);
    
	read_ppm_diretory(changed_dir, tiles_list);


	free(changed_dir);


}

