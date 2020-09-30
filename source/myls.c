#include "dependencies.h"

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent* file;

    // Check for the appropriate number of arguments
    if (argc<2)
    {
        // Open the current working directory and
        // print all the files or directories inside
        dir = opendir(".");
        while (file = readdir(dir))
        {
            printf("%s  ",file->d_name);
        }
        printf("\n");
        closedir(dir);
    }
    else if (argc==2)
    {
        // Take the directory name as the input and open the directory
        // and repeat the same process as above.
        char *path = argv[1];
        printf("Directory Name: %s\n",path);
        dir = opendir(path);
        if (dir==NULL)
        {
            printf("Unable to read directory.\n");
            exit(1);
        }
        while (file = readdir(dir))
        {
            printf("%s  ",file->d_name);
        }
        closedir(dir);
        printf("\n");
    }
    // If the arguments are neither of above cases, then throw an error
    else
    {
        printf("Invalid Arguments.\n");
        exit(1);
    }
}