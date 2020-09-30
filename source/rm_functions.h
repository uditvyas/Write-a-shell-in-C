#include "dependencies.h"

// Function to Delete a single file 
void delete_file(char *target)
{
    if (remove(target)==0)
    {
        printf("Deleted: %s\n",target);
    }
    else
    {
        printf("Failed to delete.\n");
    }
}

// Function to check for -r flag
int check_r(int argc, char *argv[])
{
    int r = 0;
    for (int i = 1; i<argc;i++)
    {   
        if (strcmp(argv[i],"-r")==0)
        {
            r = 1;
        }
    }
    return r;
}

// Function to delete a directory
void delete_dir(char *target_dir)
{
    DIR *dir = opendir(target_dir);
    if (dir == NULL)
    {
        printf("Error! Cannot Open Directory.\n");
        exit(1);
    }
    else
    {
        struct dirent* file;
        struct stat stats;
        char *name = (char *)malloc(1024*sizeof(char));
        while (file = readdir(dir))
        {
            // Checking all components of a directory
            // Continue if '.' and '..' are found
            if (strcmp(file->d_name,".")==0 || strcmp(file->d_name,"..")==0)
            {
                continue;
            }
            char *copy = (char *)malloc(1024*sizeof(char));
            strcpy(copy,target_dir);
            name = strcpy(name,target_dir);
            name = strcpy(name,strcat(name,"/"));
            name = strcat(name,file->d_name);
            stat(name,&stats);
            // if a directory is encountered inside the directory
            // Recursively call the delete_dir function
            if (S_ISDIR(stats.st_mode))
            {
                delete_dir(name);
            }
            // If the component is file, call the delete_file function
            else if (access(name,F_OK)==0)
            {
                delete_file(name);
            }
            else
            {
                printf("Error!\n");
            }
            free(name);
        }
        // After deleting the components, delete the empty directory.
        if (rmdir(target_dir)==0)
        {
            printf("Deleted Directory: %s\n",target_dir);
        }
        else
        {
            printf("Error Removing the Directory.\n");
        }
    }
    closedir(dir);
}