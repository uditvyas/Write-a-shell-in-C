#include "dependencies.h"
#include "cp_functions.h"

// Calling functions from the header "cp_functions.h"
void write_2_dir(char *destination,char *source, FILE *file);
void file_2_file(char *destination,char *source,FILE *file);
void dirfiles_2_dirfiles(char *source, char *destination);
void dir_2_dir(char *source_dir, char *dest_dir, int argc);
int check_r(int argc, char *argv[]);

// MAIN FUNCTION
int main (int argc, char * argv[])
{
    // Throw an error if number of arguments is less than 3
    if (argc<3)
    {
        printf("Usage Details:\ncp [OPTION]... [-T] SOURCE DEST\ncp [OPTION]... SOURCE... DIRECTORY\ncp [OPTION]... -t DIRECTORY SOURCE...\n");
        exit(1);
    }
    else if (argc == 3)
    {
        // Check for r (3 arguments are valid without r. With r, they are invalid)
        int r = check_r(argc,argv);
        if (r==0)
        {
            char *source = argv[1];
            char *destination = argv[2];
            struct stat stats;
            stat(source,&stats);
            // Directory can be copied only when there is a -r flag.
            if (S_ISDIR(stats.st_mode))
                {
                    printf("Missing -r Argument.\n");
                }
            else
            {
                // Checking for the source file
                FILE *file = fopen(source,"r");
                if (file==NULL)
                {
                    printf("Cannot Open File.\n");
                    exit(1);
                }
            
                struct stat stats;
                stat(destination,&stats);
                // If destination is a directory, invoke the function to 
                // copy the file to a directory (as defined above)
                if (S_ISDIR(stats.st_mode))
                {
                    write_2_dir(destination,source,file);
                }
                // If the destination already exists, throw an error.
                else if (access(destination,F_OK)==0)
                {
                    printf("File exists. Copy Failed\n");
                    exit(1);
                }
                // Otherwise execute the regular file copyting function (as defined above)
                else
                {
                    file_2_file(destination,source,file);
                }
                fclose(file);
            }
        }
        // -r flag is included but the number of arguments are only 3. 
        else
        {
            printf("Incomplete Information.\n");
            exit(1);
        }
    }

    // Number of arguments are greater than 3
    else
    {
        // Check for the -r flag.
        int r = check_r(argc,argv);
        if (r==0)
        {
            char *destination = argv[argc-1];
            struct stat stats;
            stat(destination,&stats);
            int isdir = 0;
            // Checking if the destination is a directory or a file.
            if (S_ISDIR(stats.st_mode))
            {
                // Destination is a directory, so copy every all sources into destination.
                for (int i = 1;i<argc-1;i++)
                {
                    char *source = argv[i];
                    struct stat stats;
                    stat(source,&stats);
                    // If a source is a directory then -r flag is needed.
                    if (S_ISDIR(stats.st_mode))
                    {
                        printf("-r not mentioned. Omitting directory %s\n",source);
                    }
                    else
                    {
                        // If source is a file, then open it, and invoke the function
                        // to copy a file to a directory (as defined above)
                        FILE *file = fopen(source,"r");
                        if (file==NULL)
                        {
                            printf("Cannot Open File: %s\n",source);
                        }
                        else
                        {
                            write_2_dir(destination,source,file);
                        }
                    }
                }
            }
            // if destination is not a directory, then multiple sources are not possible
            else
            {
                printf("Destination must be a directory for copying multiple files.\n");
            }
        }
        // The -r flag is present! Thus check again if the arguments are 4 or more.
        else
        {
            // if the arguments are 4
            if (argc == 4)
            {
                printf("4 Arguments with r.\n");
                char *source;
                char *destination;
                // Finding out the source and the destinations from the 4 input arguments
                if (strcmp(argv[argc-1],"-r")==0)
                {
                    destination = argv[2];
                    source = argv[1];
                }
                else
                {
                    destination = argv[argc-1];
                    if (strcmp(argv[1],"-r")==0)
                    {
                        source = argv[2];
                    }
                    else if (strcmp(argv[2],"-r")==0)
                    {
                        source = argv[1];
                    }
                }
                
                struct stat stats;
                stat(source,&stats);
                // If source is a directory, then call the function to
                // copy the directory to directory (as defined above)
                if (S_ISDIR(stats.st_mode))
                {
                    printf("Source is a Directory.\n");
                    printf("Create Directory if not present.\n");
                    dir_2_dir(source,destination,argc);
                }
                else
                {
                    // Source is a file
                    printf("Source is not a directory: %s\n",source);
                    FILE *file = fopen(source,"r");
                    if (file==NULL)
                    {
                        printf("Cannot Open File.\n");
                        exit(1);
                    }

                    struct stat stats;
                    stat(destination,&stats);
                    // If destination is directory, then invoke function
                    // to write file into directory (as defined above)
                    if (S_ISDIR(stats.st_mode))
                    {
                        write_2_dir(destination,source,file);
                    }
                    // If destination is a file that already exists, then throw error
                    else if (access(destination,F_OK)==0)
                    {
                        printf("File exists. Copy Failed\n");
                        exit(1);
                    }
                    // Otherwise, carry out the normal file to file copy
                    //using the function (as defined above)
                    else
                    {
                        file_2_file(destination,source,file);
                    }
                    fclose(file);
                }
            }
            // -r flag is present with more than 4 arguments
            else
            {
                printf("More than 4 Arguments with r\n");
                char *source;
                char *destination;
                int end = 0;
                // Finding the sources and destination
                if (strcmp(argv[argc-1],"-r")==0)
                {
                    destination = argv[argc-2];
                    end = argc-2;
                }
                else
                {
                    destination = argv[argc-1];
                    end = argc-1;
                }
                for (int i = 1; i < end; i++)
                {
                    if (strcmp(argv[i],"-r")==0)
                    {
                        continue;
                    }
                    else
                    {
                        source = argv[i];
                        struct stat stats;
                        stat(source,&stats);
                        // If source is a directory, then invoke
                        // the function dir_2_dir (as defined above)
                        if (S_ISDIR(stats.st_mode))
                        {
                            printf("Source is a Directory.\n");
                            dir_2_dir(source,destination,argc);
                        }
                        else
                        {
                            // Source is a file
                            printf("Source is not a directory: %s\n",source);
                            FILE *file = fopen(source,"r");
                            if (file==NULL)
                            {
                                printf("Cannot Open File.\n");
                                exit(1);
                            }

                            struct stat stats;
                            stat(destination,&stats);
                            // Check for destination, and call the appropriate function
                            // as in different cases below (similar to the above cases)
                            if (S_ISDIR(stats.st_mode))
                            {
                                write_2_dir(destination,source,file);
                            }
                            else if (access(destination,F_OK)==0)
                            {
                                printf("File exists. Copy Failed\n");
                                exit(1);
                            }
                            else
                            {
                                file_2_file(destination,source,file);
                            }
                            fclose(file);
                        }
                    }
                }
            }
        }
        
    }
    return 0;
}
// END OF MAIN