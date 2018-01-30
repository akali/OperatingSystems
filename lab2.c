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
			sleep(5);
			/* while (true) {
				// printf("%lf\n", (clock() - start) / CLOCKS_PER_SEC);
				if ((clock() - start) / CLOCKS_PER_SEC > 5) {
					break; // CLOCKS_PER_SEC is the number of ticks per second
				}
			} */
			// Checking wether we are orphant
			FILE *fout = fopen("output.txt", "w");
			// printf("%d %d\n", getpid(), getppid());
			if (getppid() != before) {
				printf("Process %d is orphan\n", getpid());
			} else {
				printf("Parent process is still running");
			}
		}
		sleep(2);
		raise(SIGKILL);
		double start = clock();
		/*while (true) {
			// printf("%lf\n", (clock() - start) / CLOCKS_PER_SEC);
			if ((clock() - start) / CLOCKS_PER_SEC > 5) {
				break; // CLOCKS_PER_SEC is the number of ticks per second
			}
		}*/

	}
	
	

	return 0;
}

