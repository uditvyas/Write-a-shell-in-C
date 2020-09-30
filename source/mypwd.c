#include "dependencies.h"

int main (int argc, char *argv[])
{
    // Defining a fixed buffer size of 128
    char dir[128];
    // Invoking the system call getcwd
    if (getcwd(dir,sizeof(dir))!=NULL)
    {
        printf("%s\n",dir);
    }
    else
    {
        printf("Error!\n");
    }
}
