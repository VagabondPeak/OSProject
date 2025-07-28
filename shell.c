/*
 * File: shell.c
 * Authors: Francisco Ortega, Peter Nguyen, Kathy Nguyen
 * Assignment: Mini Shell
 * Due date: 07/28/2025
 *
 * Description:
 *   In this program ,we have created a Unix-like shell in the C programming
 language. It will read user input, parse the command, and search for an executable
 in the system path. It also has the ability to handle errors should they arise.
 */


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
// Reads a line of input from the user and returns it
void readCommand(char* inputBuffer) {
  if (fgets(inputBuffer, MAX_CMDLINE, stdin) == NULL) {
    perror("fgets failed");
    exit(1);
  }

  // Remove trailing newline character
  size_t len = strlen(inputBuffer);
  if (len > 0 && inputBuffer[len - 1] == '\n') {
    inputBuffer[len - 1] = '\0';
  }
}
// Parses the input string into arguments
void parseCommand(char* inputBuffer, command_t* cmd) {
  char* token = strtok(inputBuffer, " ");
  int index = 0;
  
  // loop through each toke in the argv
  while (token != NULL && index < MAX_CMDLINE - 1) {
    cmd->argv[index++] = token;
    token = strtok(NULL, " ");
  }

  cmd->argv[index] = NULL;  // null-terminate for execv

  // store the num of arguments
  cmd->argc = index;
}
// Parses the system PATH into an array of directories
int parsePath(char* dir[]) {
  char* pathEnv = getenv("PATH");
  char* token = strtok(pathEnv, ":");
  int count = 0;

  // loop throug each token in the path string
  while (token != NULL && count < MAX_PATHS) {
    dir[count++] = token;
    token = strtok(NULL, ":");
  }

  // at the end of the array, mark null
  dir[count] = NULL;  // null-terminate
  return count;
}
// Searches for the command in the directories from PATH
char* lookupPath(char* cmdName, char* dir[]) {
  static char fullPath[MAX_CMDLINE];

  // If command already has '/' (e.g., ./a.out), don't search PATH
  if (strchr(cmdName, '/') != NULL) {
    if (access(cmdName, X_OK) == 0) {
      return cmdName;
    }
    return NULL;
  }
  // loop through directory in path array
  for (int i = 0; dir[i] != NULL; i++) {
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dir[i], cmdName);
    if (access(fullPath, X_OK) == 0) {

      // if it exists and is executable, we will return the full path
      return fullPath;
    }
  }

  return NULL;  // not found
}


// this is where the main loop of the shell is
int main() {
  
  char inputBuffer[MAX_CMDLINE];
  char* pathDirs[MAX_PATHS];
  command_t command;

  // while true, it will continuously prompt the user to input a command
  while (1) {
    printPrompt();
    readCommand(inputBuffer);

    // if user exits, break out of shell loop and terminate
    if (strcmp(inputBuffer, "exit") == 0) {
      break;
    }

    // parse user command
    parseCommand(inputBuffer, &command);
    if (command.argc == 0) {
      continue;  // empty input
    }

    parsePath(pathDirs);
    char* cmdPath = lookupPath(command.argv[0], pathDirs);

    // if command not found, error
    if (cmdPath == NULL) {
      printf("Command not found: %s\n", command.argv[0]);
      continue;
    }

    // creates the a new process
    pid_t pid = fork();
    if (pid == 0) {
      // In child process
      execv(cmdPath, command.argv);
      perror("execv failed");
      exit(1);
    } else if (pid > 0) {
      // In parent process, will wait until child is terminated
      wait(NULL);
    } else {
      perror("fork failed");
    }
  }

  // we have terminated/exited
  printf("MiniShell terminated.\n");
  return 0;
}
