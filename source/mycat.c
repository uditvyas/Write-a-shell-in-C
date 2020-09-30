#include "dependencies.h"

int main (int argc, char *argv[])
{
    // Checking for Appropriate number of arguments
    if (argc<2)
    {
        printf("Invalid Arguments\nType: 'cat filename'");
        return 0;
    }
    else
    {   
        // For each file to be displayed, open the file and print its contents
        for (int i=1;i<argc;i++)
        {
            printf("\nFile name: %s \n",argv[i]);
            FILE *file = fopen(argv[i],"r");
            if (file==NULL)
            {
                printf("Mycat: Cannot open file.\n");
                exit(1);
            }
            else
            {
                size_t linesize = 256;
                char *line = (char *)malloc(linesize*sizeof(char));
                ssize_t num = getline(&line,&linesize,file);
                while (num>0)
                {
                    printf("%s",line);
                    num = getline(&line,&linesize,file);
                }
            }
            printf("\n************************************************\n");
        }
    }
    return 0;
}