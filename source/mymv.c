#include "dependencies.h"

int main (int argc, char *argv[])
{
    // Checking for the appropriate number of arguments
    if (argc <3)
    {
        printf("Format: mv source destination.\n");
        exit(0);
    }
    // Sources are multiple, thus destination has to be a directory
    else if (argc>3)
    {
        // Check if the destination is a directory or not
        char *dest = argv[argc-1];
        struct stat stats;
        stat(dest,&stats);
        if (S_ISDIR(stats.st_mode))
        {
            // Destination is Directory
            char *dir = (char *)malloc(32*sizeof(char));
            char *copy = (char *)malloc(32*sizeof(char));
            for (int i = 1; i<argc-1; i++)
            {
            
                strcpy(dir,argv[argc-1]);
                char *source = argv[i];
                strcpy(copy,argv[argc-1]);
                char *destination = strcat(strcat(dir,"/"),source);
                printf("Destination: %s\n",destination);
                // Checking if the destination is possible or not
                int status = rename(source,destination);
                if (status!=0)
                {
                    printf("Failed to Move: %s\n",source);
                }
            }
            free(dir);
            free(copy);
        }
        // If Destination is not a directory, throw an error
        else
        {
            printf("Destination '%s' is not a Directory!\n",dest);
            exit(1);
        }
    }
    // Number of arguments are 3. Thus simple application of the rename function will work
    else
    {
        char *source = argv[1];
        char *destination = argv[2];
        int status = rename(source,destination);
        if (status!=0)
        {
            printf("Failed to Move: %s\n",source);
            exit(1);
        }
    }
    return 0;
}