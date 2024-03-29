/*
Max Paulus 69457762
Professor Harris
ICS53
Lab2 - Shell Lab
*/

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>
#include <signal.h>

#define MAXCHARS 100
#define MAXARGS 20

extern char** environ; //defined in libc

int parse(char*, char**);

int main() {
  char line[MAXCHARS], lastChar, * argv[MAXARGS];
  int pid, status, bg;

  while(1) {
    printf("prompt> ");
    fgets(line, MAXCHARS, stdin); //get the line
    if (feof(stdin))
      exit(0);

    bg = parseline(line, argv);

    if (!strcmp(argv[0], "quit"))
      exit(0);

    pid = fork(); //create a clone of the current process
    if(pid < 0) {
      fprintf(stderr, "Error forking\n");
    }
    else if (pid == 0) {
    //child process code
      execve(argv[0], argv, environ);
      //this line replaces the current process with the one specified
      //in argv[0].
      fprintf(stderr, "%s: Command not found.\n", argv[0]);
      exit(-1);
    }
    else {
    //parent process code
      if (bg) {
        printf("Both processes running concurrently.\n");
      }
      else {
        // run the child process in the foreground
        wait(&status);
      }
    }

  }
  kill(0, SIGKILL);
  wait(NULL); //kill and reap the background children (so morbid lol)
  return 0;
}

 /* parseline - Parse the command line and build the argv array

  NOTE: This function is taken straight from the ICS53 textbook! 
  I, Max Paulus, do not claim to have written ANY of the following
  code!! Professor Harris said it was ok to use this.
  */
int parseline(const char *cmdline, char **argv) 
{
  static char array[MAXCHARS]; /* holds local copy of command line */
  char *buf = array;          /* ptr that traverses command line */
  char *delim;                /* points to first space delimiter */
  int argc;                   /* number of args */
  int bg;                     /* background job? */

  strcpy(buf, cmdline);
  buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
  while (*buf && (*buf == ' ')) /* ignore leading spaces */
    buf++;

    /* Build the argv list */
  argc = 0;
  while ((delim = strchr(buf, ' '))) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;

    while (*buf && (*buf == ' ')) /* ignore spaces */
      buf++;
  }
  argv[argc] = NULL;

  if (argc == 0)  /* ignore blank line */
    return 1;

    /* should the job run in the background? */
  if ((bg = (*argv[argc-1] == '&')) != 0)
    argv[--argc] = NULL;

  return bg;
}