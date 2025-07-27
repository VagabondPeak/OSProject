//libaries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

//Constants LINE, MAX_ARGS, MAX_ARG_LEN, MAX_PATHS, MAX_PATH_LEN, WHITESPACE, TRUE

//function to prompt the user
void printPrompt()
{
  printf("osshell$ ");
  fflush(stdout);
}


//function to read the input
void readCommand(char *buffer)
{
  fgets(buffer, LINE, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
}

//function the parases commands into the command struct
void parseCommand(char *input, struct command_t *cmd)
{
  cmd->argc = 0;
  char *token = strtok(input, WHITESPACE);
  while (token != NULL && cmd->arg
}
