/*
 * File: shell.h
 * Authors: Francisco Ortega, Peter Nguyen, Kathy Nguyen
 * Assignment: Mini Shell
 * Due date: 07/28/2025
 *
 * Description:
 *   In this program, we have created a header file for the mini shell program.
 *   It will hold the constants and function prototypes for the shell implementation. 
 */



//head file to define some variables constants, a struct for command

#ifndef SHELL_H
#define SHELL_H


// defined max values
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

// parse input buffer into command and args
void parseCommand(char* inputBuffer, command_t* cmd);

// parses path var into array
int parsePath(char* dir[]);

// search for command in directories and return full path if found
char* lookupPath(char* cmdName, char* dir[]);

#endif
