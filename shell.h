//head file to define some variables constants, a struct for command

#ifndef SHELL_H
#define SHELL_H

#define LINE 80 //max line length
#define MAX_ARGS 64 //max num of args
#define MAX_ARG_LEN 16 //max arg length
#define MAX_PATHS 64 //max num of paths
#define MAX_PATH_LEN 96 //max path length
#define MAX_CMDLINE 1024 //input buffer size
#define WHITESPACE " \t\n" //whitespace separators
#define TRUE 1 //make a true value 1

#ifndef NULL
#define NULL ((void *)0)
#endif

//typedef struct to group cmd variables together
typedef struct {
  char *name;
  int argc;
  char *argv[MAX_ARGS];
} command_t;


//prototypes for commands
void readCommand(char* inputBuffer);
void parseCommand(char* inputBuffer, command_t* cmd);
int parsePath(char* dir[]);
char* lookupPath(char* cmdName, char* dir[]);

#endif
