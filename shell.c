#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>

extern char **environ; //defined in libc

int main(int argc, char **argv) {


  char command[20];
  char lastChar; //for checking if last character is'&'
  int pid;
  int status;

  do {
    printf("prompt> ");
    scanf("%s", command);
    lastChar = command[strlen(command) - 1];
    if (lastChar == '&') command[strlen(command) - 1] = '\0';

    pid = fork(); //create a clone of the current process
    if(pid < 0) {
      printf("Error forking\n");
      exit(1);
    }
    else if (pid == 0) {
    //child process code
      execve(command, argv, environ);
      //this line replaces the current process with the one specified in
      //the command variable.
    }
    else { 
    //parent process code
      if (lastChar != '&') {
      // run the child process in the foreground
        printf("Parent Waiting\n");
        wait(&status);
        printf("Parent resumed\n");
      }
      else {
        printf("Both processes running concurrently.\n");
      }
    }

  } while (strcmp("quit", command));

  return 0;
}