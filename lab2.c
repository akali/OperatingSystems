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

int main(int argc, char *argv[]) {
	pid_t pid = fork();
	
	printf("Root process pid = %d\n", getpid());
	
	// Creating orphant
	if (pid < 0) {
		printf("Error!");
	} else {
		if (pid == 0) {
			// We are in child process
			// Orphan process
			// Let's make a action which takes a lot of time
			// Actually our program will do nothing for 10 secs then ends process
			double start = clock();
			pid_t before;
			printf("parent before is %d\n", before = getppid());
			sleep(10);
			if (getppid() != before) {
				printf("Process %d is orphan\n", getpid());
			} else {
				printf("Parent process is still running");
			}
		} else {
			printf("First child pid = %d\n", pid);
			// We are in root process 
			// Let's make zombie process
			pid_t pid = fork();
			if (pid < 0) {
				printf("Forking error!");
			} else {
				if (pid == 0) {
					// We are in zombie process
					exit(0);
				} else {
					printf("Second child pid = %d\n", pid);
					// Wait a bit to kill current process before orphan process ends and after zombie process ends
					sleep(6);
					char call[256];
					sprintf(call, "ps aux | grep \"%d\"", pid);
					// sprintf(call, "cat /proc/%d/status", pid);
					system(call);
					raise(SIGKILL);
				}
			}
		}
	}
	
	

	return 0;
}

