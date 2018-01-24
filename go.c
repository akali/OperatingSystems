#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main() {
	pid_t pid;

	char *const ps[] = {"/bin/ls", "-l", NULL};

	if ((pid = fork()) < 0) {
		printf("fork() error\n");
	} else if (!pid) {
		execvp("ls", ps);
		printf("return not expected. ");
	}

	// return 0;
}

