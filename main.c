#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>

#define MAXLEN 256
#define STACK_SIZE 10

#define true 1
#define false 0

char *args[MAXLEN], *cmd;

char argsStack[STACK_SIZE][MAXLEN];
int curPos = 0;

void history() {
	int cur = 1;
	for (int i = 0; i < STACK_SIZE; ++i) {
		int j = (curPos - i + STACK_SIZE) % STACK_SIZE;
		if (argsStack[j] == NULL || strlen(argsStack[j]) == 0) break;
		printf("%d. %s\n", cur++, argsStack[j]);
	}
}

void *executionThread(void* vargs) {
	printf("Starting execvp in %d, with parent %d\n", getpid(), getppid());
	int errcode = execvp(cmd, args);
	printf("Ending execvp in %d, with parent %d\n", getpid(), getppid());
	printf("Some error occured: %d\n", errcode);
	printf("Errno: %d\n", errno);
	return NULL;
}

void execute() {
	pthread_t tid;
	
	pthread_create(&tid, NULL, executionThread, NULL);
	pthread_join(tid, NULL);

	raise(SIGUSR1);
}

int main(int argc, char *argv[]) {
  while (true) {
    printf("Shell) ");
    fflush(stdout);
    char tmp[MAXLEN];
    fgets(tmp, MAXLEN-1, stdin);

    char *separator = " \n\t\a";
    
    char *p = strtok(tmp, separator);

    int cnt = 0;
		cmd = NULL;
    cmd = p; p = strtok(NULL, separator);
    args[cnt++] = cmd;
    while (p != NULL) {
      args[cnt++] = p;
      p = strtok(NULL, separator);
    }
    
		/*for (int i = 0; i < cnt; ++i) {
			printf("!!! -> %s\n", args[i]);
		}*/

    if (cmd == NULL) continue;
		
		char background = false;
		if (cnt) background = strcmp(args[cnt-1], "&") == 0;

    if (background) args[cnt-1] = NULL;
    
    ++curPos;
    curPos %= STACK_SIZE;
    
		strcpy(argsStack[curPos], tmp);

    if (!strcmp(args[0], "history")) {
      history();
      continue;
    }
    
    if (!strcmp(args[0], "exit")) {
    	break;
    }
    
    pid_t pid = fork();

    if (pid == 0) {
    	execute();
    } else if (pid > 0) {
    	if (!background) {
    		wait(NULL);
    	}
    }
	}
	printf("Have a nice day. Good bye!\n");
	return 0;
}

