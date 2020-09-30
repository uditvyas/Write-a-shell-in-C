#include "dependencies.h"

// Function to Scan the User input
char *scan_terminal(void)
{   
    char *line;
    size_t linesize = 32;
    line = (char *)malloc(linesize * sizeof(char));
    if (line==NULL)
    {
        printf("Unable to allocate Memory.");
        exit(1);
    }
    // reading one line from the terminal
    else
    {
        getline(&line,&linesize,stdin);
    }
    return line;
}

// Function to split the user inputs into tokens for execution
char **split_input(char *line)
{
    int i = 0;
    int def_size = 32;
    char **args = malloc(def_size*sizeof(char*));
    char *delimiter = " ";
    // Splitting the line with the " " delimiter
    char *split = strtok(line,delimiter);
    while (split!=NULL)
    {
        args[i] = split;
        i++;
        if (i>def_size)
        {
            // Reallocating memory of the tokens if there is an overflow
            def_size = def_size + 32;
            args = realloc(args,def_size*sizeof(char*));
            if (!args)
            {
                printf("Memory Allocation Problem.");
                exit(1);
            }
        }
        // NULL terminating the pointer array
        split = strtok(NULL,delimiter);
    }
    args[i] = NULL;
    return args;
}

// Function to Execute the commands
void execute(char **args)
{   
    int and = 0;
    int i = 0;
    // This is an array of the commands that are customly made
    char *mycommands[9] = {"ls","grep","mv","cp","cd","pwd","rm","chmod","mkdir"};
    int num_mycommands=9;

    //Identifying and Removing '&'
    while(args[i]) i++;
    if (strcmp(&args[i-1][strlen(args[i-1])-2],"&\n")==0)
    {
        and = 1;
        args[i-1][strlen(args[i-1])-2]='\0';
    }
    
    //Replacing the Newline Characters with end of string characters
    if (args[0][strlen(args[0])-1]=='\n')
    {
        args[0][strlen(args[0])-1] = '\0';
    }

    // If the user command matches with the command made in the assignment, then
    // the program adds a ./ in the front to execute built executable and not the default command
    for (int i = 0 ; i<num_mycommands;i++)
    {
        if (strcmp(args[0],mycommands[i])==0)
        {
            char *name = (char *)malloc(32*sizeof(char));
            char *slash = "./";
            strcpy(name,slash);
            strcat(name,args[0]);
            args[0] = name;
        }
    }

    printf("Executing Command: %s\n",args[0]);

    // If the & is not present, that is, run all the program in the foreground
    if (and == 0)
    {
        // Forking to create a child process and simply executeing execvp in the child process and making the parent wait
        int rc = fork();
        int status;
        if (rc<0)
        {
            printf("Fork Error");
        }
        else if (rc==0)
        {
            int i = 1;
            while (args[i])
            {
                if (args[i][strlen(args[i])-1]=='\n')
                {
                    args[i][strlen(args[i])-1] = '\0';
                }
                i++;
            }
            // Invoking Execvp
            execvp(args[0],args);
            printf("Command Not Found!\n");
            exit(1);
        }
        // Parent process is waiting
        else
        {
            int w = waitpid(rc,&status,0);
        }
    }
    // If & is present in the command
    else
    {
        // The fork process is similar except for the parent process will now 
        // not wait for the child process, and the child process is now moved in
        // another process group so as to continue its execution in the background
        int rc = fork();
        int status;
        if (rc<0)
        {
            printf("Fork Error");
        }
        else if (rc==0)
        {
            setpgid(0,0);
            int i = 1;
            while (args[i])
            {
                if (args[i][strlen(args[i])-1]=='\n')
                {
                    args[i][strlen(args[i])-1] = '\0';
                }
                i++;
            }
            fclose(stdout);
            execvp(args[0],args);
            printf("Command Not Found!\n");
        }
        else
        {
            printf("Executing Command %s with PID: %d\n",args[0],rc);
        }
    }
}