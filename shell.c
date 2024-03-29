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

  while(1) {
    printf("prompt> ");
    scanf("%s", command);
    lastChar = command[strlen(command) - 1];
    if (lastChar == '&') command[strlen(command) - 1] = '\0';

    if (!strcmp("quit", command)) break;

    pid = fork(); //create a clone of the current process
    if(pid < 0) {
      printf("Error forking\n");
    }
    else if (pid == 0) {
    //child process code
      execve(command, argv, environ);
      //this line replaces the current process with the one specified in
      //the command variable.
      printf("%s: Command not found.\n", command);
      exit(0);
    }
    else { 
    //parent process code
      if (lastChar != '&') {
      // run the child process in the foreground
        //printf("PARENT: suspending execution\n");
        wait(&status);
        //printf("PARENT: resumed execution\n");
      }
      else {
        printf("Both processes running concurrently.\n");
        sleep(3);
        printf("Parent while loop ending\n");
      }
    }

  }

  return 0;
}