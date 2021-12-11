#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
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
    free(changed_dir);

    return 0;
}