#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>



int main() {


  char command[20];
  char lastChar; //for checking if last character is'&'
  int pid;
  int status;

  do {
    printf("prompt> ");
    scanf("%s", command);
    lastChar = command[strlen(command) - 1];

    pid = fork();
    if(pid < 0) {
      printf("\n Error forking");
      exit(1);
    }
    else if (pid == 0) { //child process code
      execve(command, "", "");
    }
    else { //parent process code
      if (lastChar != '&') { // run the child process in the foreground
        wait(&status);
      }
    }

  } while (strcmp("quit", command));
  
  int status;
  int pid;
  pid=fork();
  if(pid<0)
  {
      printf("\n Error ");
      exit(1);
  }
  else if(pid==0)
  {
      printf("\n Hello I am the child process ");
      printf("\n My pid is %d ",getpid());
      exit(0);
  }
  else
  {
      wait(&status);
      printf("\n Hello I am the parent process ");
      printf("\n My actual pid is %d \n ",getpid());
      exit(1);
  }

  return 0;
}