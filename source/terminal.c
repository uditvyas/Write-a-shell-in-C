#include "dependencies.h"
#include "terminal_functions.h"

// Including functions from the supporting headerfile
char *scan_terminal(void);
char **split_input(char *line);
void execute(char **args);

// Function to loop infinitely for the terminal
void terminal()
{
    while (1)
    {
    printf("\033[1;32m");
    printf("terminal>>");
    printf("\033[0m");
    // Scanning and Splitting the input arguments
    char *line = scan_terminal();
    char **args = split_input(line);
    execute(args);
    free(line);
    free(args);
    }
}

// int main invokes the terminal function
int main (int argc, char *argv[])
{
    char *args[] = {"clear",NULL};
    execute(args);
    printf("\033[1;31m");
    printf("\n**************************** Welcome to My Shell ****************************\n\n");
    printf("\033[0m");
    terminal();
}