#include "dependencies.h"

int main (int argc, char *argv[])
{
    // If inappropriate number of arguments
    if (argc!=2)
    {
        printf("Usage: cd path\n");
    }
    else
    {
        // Uses System command chdir to change the current working directory
        if (chdir(argv[1])==0)
        {
            printf("Changed directory to: %s\n",argv[1]);
        }
        else
        {
            printf("Invalid Path\n");
        }
    }
}