#include "dependencies.h"

int main (int argc, char *argv[])
{
    // Checking for the appropriate number of arguments
    if (argc<2)
    {
        printf("mygrep: searchterm [file...]\n");
        exit(1);
    }
    else if (argc > 2)
    {
        for (int i=2;i<argc;i++)
        {
            // Check for each file
            printf("File name: %s\n",argv[i]);
            FILE *file = fopen(argv[i],"r");
            if (file==NULL)
            {
                printf("Mygrep: Cannot open file.\n");
                exit(1);
            }
            else
            {
                // Create a buffer for the search token/s   
                size_t linesize = 256;
                char *line = (char *)malloc(linesize*sizeof(char));
                char *search = argv[1];
                if (line==NULL)
                {
                    printf("Unable to allocate Memory.");
                    exit(1);
                }
                else
                {
                    // Parse through the files to get the match string and
                    // print the string if found
                    ssize_t num = getline(&line,&linesize,file);
                    char *status = NULL;
                    while (num>0)
                    {
                        status = strstr(line,search);
                        if (status!=NULL)
                        {
                            printf("%s",line);
                        }
                        num = getline(&line,&linesize,file);
                    }
                free(line);
                free(status);
                }
            }
            fclose(file);
        }
    }
    // if argument equal to 2, take the input from the user from the stdin
    else
    {
        size_t linesize = 256;
        char *line = (char *)malloc(linesize*sizeof(char));
        char *search = argv[1];
        // Creating Buffer
        if (line==NULL)
        {
            printf("Unable to allocate Memory.");
            exit(1);
        }
        else
        {
            // Take the user input and check for the string match
            printf("Enter the Line: ");
            ssize_t num = getline(&line,&linesize,stdin);
            char *status = NULL;
            if (num>0)
            {
                status = strstr(line,search);
                if (status!=NULL)
                {
                    printf("Matched: %s",line);
                }
            }
        free(line);
        }
    }
    return 0;
}