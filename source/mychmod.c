#include "dependencies.h"

int main(int argc, char *argv[])
{  
    // Checking for appropriate number of arguments
    if (argc<3)
    {
        printf("Usage: chmod MODE FILE\n");
    }
    else
    {
        // Using the chmod system call to change the permissions of the file provided
        // in the subsequent arguments
        mode_t mode = atoi(argv[1]);
        for (int i=2;i<argc;i++)
        {
            char *file=argv[i];
            printf("File: %s    Mode: %d    ",file,mode);
            if(chmod(file,mode)==0)
            {
                printf("Permissions Changed.\n");
            }
            else
            {
                printf("Error! %s\n",strerror(errno));
            }

        }
    }
    return 0;
}