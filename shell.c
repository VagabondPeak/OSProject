//libaries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

//function to prompt the user
void printPrompt()
{
  printf("osshell$ ");
  fflush(stdout);
}
