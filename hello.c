#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc == 2) {
    sleep(2);
	  printf("Hi %s! You ROCK!\n", argv[1]);
    sleep(2);
  }
  else {
    printf("Usage: hello <someones's name>\n");
  }
	return 0;
}
