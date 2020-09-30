#include "dependencies.h"
#include "rm_functions.h"

void delete_file(char *target);
int check_r(int argc, char *argv[]);
void delete_dir(char *target_dir);

int main (int argc, char* argv[])
{
    // Checking for the appropriate number of arguments
    if (argc<2)
    {
        printf("Usage: rm target [-r option]\n");
    }
    else
    {
        int r = check_r(argc,argv);
        for (int i = 1; i<argc;i++)
        {   
            if (strcmp(argv[i],"-r")==0)
            {
                continue;
            }
            else
            {
                char *target = argv[i];            
                struct stat stats;
                stat(target,&stats);
                printf("Target: %s\n",target);
                // if target is a directory, then invoke the function, delete_dir()
                if (S_ISDIR(stats.st_mode)!=0)
                {
                    if (r == 1)
                    {
                        // char *current = 
                        delete_dir(target);
                    }
                    else printf("%s is a directory. Include -r to delete.\n",target);

                }
                // else if target is a file, invoke the delete_file function
                else if (access(target,F_OK)==0)
                {
                    delete_file(target);
                }
                else
                {
                    printf("%s: File Not Found.\n",target);
                }
            }
        }
    }
    return 0;
}