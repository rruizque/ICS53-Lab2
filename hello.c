#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc == 2) {
    sleep(2);
	  printf("Hi %s! You ROCK!\n", argv[1]);
    sleep(2);
  }
  else {
    printf("Hello: Incorrect args\n");
  }
	return 0;
}
