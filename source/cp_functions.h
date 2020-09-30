#include "dependencies.h"

// Function to write a file into a directory
void write_2_dir(char *destination,char *source, FILE *file)
{
    char *dir = (char *)malloc(32*sizeof(char));
    strcpy(dir,destination);
    char *address = strcat(strcat(dir,"/"),source);
    printf("Address: %s\n",address);
    // Checking if the file already exists or not 
    if (access(address,F_OK)==0)
    {
        printf("File exists. Copy Failed\n");

    }
    // File does not exist. Thus makes a copy.
    else
    {
        FILE *dest_file = fopen(address, "w");
        if (dest_file==NULL)
        {
            printf("Failed to create a copy.\n");
            exit(1);
        }
        else
        {
            int ch;
            while(fread(&ch,sizeof(char),1,file))
            {
                fwrite(&ch,sizeof(char), 1,dest_file);
            }
        }
        fclose(dest_file);
    }
    free(dir);
}

// Function to copy a file in the same directory or to a complete path given
void file_2_file(char *destination,char *source,FILE *file)
{
    // Opens a file stream
    FILE *dest_file = fopen(destination, "w");
    if (dest_file==NULL)
    {
        printf("Failed to create a copy.\n");
        exit(1);
    }
    else
    {
        int ch;
        while(fread(&ch,sizeof(char),1,file))
        {
            fwrite(&ch,sizeof(char), 1,dest_file);
        }
    }
    fclose(dest_file);
}

// Function to copy all files within a directory to another directory
// Support function for void dir_2_dir()
void dirfiles_2_dirfiles(char *source, char *destination)
{
    printf("FINAL STAGE\n");
    DIR *s_dir;
    struct dirent* s_file;
    printf("source: %s",source);
    s_dir = opendir(source);
    
    if (s_dir==NULL)
    // checking for the presence of source directory
    {
        printf("Error!\n");
        exit(1);
    }
    while (s_file = readdir(s_dir))
    {
        // Reading every file in the source if it exists
        if(access(s_file->d_name,F_OK)==0)
        {
            char *copy_dest = (char *)malloc(32*sizeof(char));
            strcpy(copy_dest,destination);
            char *name = s_file->d_name;
            FILE *file = fopen(name,"r");
            // Making the final copy destination
            char *outname = (char *)malloc(32*sizeof(char));
            strcpy(outname,strcat(strcat(copy_dest,"/"),name));
            printf("Saving Name with path: %s   ",outname);
            // Creating a file stream to write the copied file
            FILE *out_file = fopen(outname,"w");
            if (file==NULL)
            {
                printf("Could not Copy file: %s",name);
            }
            else
            {
                printf("Copying from Directory to Directory\n");
                int ch;
                while(fread(&ch,sizeof(char),1,file))
                {
                    fwrite(&ch,sizeof(char),1,out_file);
                }
            }
            free(outname);
            free(copy_dest);
        }
    }
    closedir(s_dir);
}

// Function to make a copy of the directory
void dir_2_dir(char *source_dir, char *dest_dir, int argc)
{
    DIR *s_dir;
    DIR *d_dir;
    struct dirent* s_file;
    struct dirent* d_file;
    struct stat stats;
    stat(dest_dir,&stats);
    // Checking for source directory
    if (S_ISDIR(stats.st_mode))
    {
        printf("Destination exist.\n");
        dest_dir = strcat(strcat(dest_dir,"/"),source_dir);
        if (mkdir(dest_dir,0777)==0)
        {
            printf("Destination for pasting: %s\n",dest_dir);
            dirfiles_2_dirfiles(source_dir,dest_dir);
        }
        else
        {
            printf("Copy Error!\n");
        }
    }
    else
    {
        // If destination does not exist, and if there is only one source and destination
        // i.e. argc = 4, then create a new directory, otherwise throw error.
        printf("Destination Does not exists.\n");
        if (argc==4)
        {
            if (mkdir(dest_dir,0777)==0);
            {
                printf("Directory Created: %s\n",dest_dir);
                dirfiles_2_dirfiles(source_dir,dest_dir);
            }
        }
        else
        {
            printf("Target '%s' does not exist.\n",dest_dir);
            exit(1);
        }
    }
}

// Function to check for the -r flag
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