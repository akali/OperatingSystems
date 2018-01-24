#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

const int MAXLEN = 256;

#define true 1
#define false 0

char* history() {
  return "history";
}

int main(int argc, char *argv[]) {
  pid_t pid = fork();

  char *my[argc];

  for (int i = 1; i < argc; ++i) {
    int s=0, len=strlen(argv[i]);
    if (i==1) {
      len+=strlen("/bin/");
      s += strlen("/bin/");
    }
    my[i-1] = malloc(len);

    if (i == 1) {
      strcpy(my[i-1], "/bin/");
    }

    strcpy(my[i-1]+s, argv[i]);

    printf("%s\n", my[i-1]);
  }

  // my[argc-1] = NULL;

  pid_t pid = fork();

  if (!pid) {
    printf("%d\n", execvp(argv[0], my));
    printf("%d\n", errno);
  }
  // return 0;
}

