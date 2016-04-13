#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>



int main() {


  // char command[20];

  // do {
  //   printf("\nprompt> ");
  //   scanf("%s", command);


    
  // } while (!strcmp("quit", command) == 0);
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