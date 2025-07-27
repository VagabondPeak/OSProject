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

  while (token != NULL && index < MAX_CMDLINE - 1) {
    cmd->argv[index++] = token;
    token = strtok(NULL, " ");
  }

  cmd->argv[index] = NULL;  // null-terminate for execv
  cmd->argc = index;
}
// Parses the system PATH into an array of directories
int parsePath(char* dir[]) {
  char* pathEnv = getenv("PATH");
  char* token = strtok(pathEnv, ":");
  int count = 0;

  while (token != NULL && count < MAX_PATHS) {
    dir[count++] = token;
    token = strtok(NULL, ":");
  }

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

  for (int i = 0; dir[i] != NULL; i++) {
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dir[i], cmdName);
    if (access(fullPath, X_OK) == 0) {
      return fullPath;
    }
  }

  return NULL;  // not found
}

int main() {
  char inputBuffer[MAX_CMDLINE];
  char* pathDirs[MAX_PATHS];
  command_t command;

  while (1) {
    printPrompt();
    readCommand(inputBuffer);

    if (strcmp(inputBuffer, "exit") == 0) {
      break;
    }

    parseCommand(inputBuffer, &command);
    if (command.argc == 0) {
      continue;  // empty input
    }

    parsePath(pathDirs);
    char* cmdPath = lookupPath(command.argv[0], pathDirs);

    if (cmdPath == NULL) {
      printf("Command not found: %s\n", command.argv[0]);
      continue;
    }

    pid_t pid = fork();
    if (pid == 0) {
      // In child process
      execv(cmdPath, command.argv);
      perror("execv failed");
      exit(1);
    } else if (pid > 0) {
      // In parent process
      wait(NULL);
    } else {
      perror("fork failed");
    }
  }

  printf("MiniShell terminated.\n");
  return 0;
}
