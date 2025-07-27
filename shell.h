//head file to define some variables

#define LINE 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_PATHS 64
#define MAX_PATH_LEN 96
#define WHITESPACE " \t\n"
#define TRUE 1

struct commmand_t {
  char *name;
  int argc;
  char *argv[MAX_ARGS];
}
