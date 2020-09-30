#include "dependencies.h"

int main (int argc, char *argv[])
{
    // Checking for appropriate number of arguments
    if (argc<2)
    {
        printf("Missing arguments");
        exit(1);
    }
    // For every argument create a directory with default permissions
    for (int i=1;i<argc;i++)
    {
        char *dirname = argv[i];
        if (mkdir(dirname,0777)==0);
        {
            fprintf(stderr,"Directory Created: %s\n",dirname);
        }
    }
}
