#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 6

// Following demonstrates creating a pipe in the parent process
// Passing it down to the child to write to
// And reading the results back in the parent

int main (int argc, char *argv[]) {
	int p[2];
	char inbuf[MSGSIZE];

	// Create pipe
	int res = pipe(p);

	if (res < 0) {
		exit(1);
	}

	pid_t pid = fork();

	if (pid < 0) {
		printf("Error forking child");
	} else if (pid == 0) {
		write(p[1], "hello", MSGSIZE);
		write(p[1], "doors", MSGSIZE);
	} else {
		wait(NULL);
		for (int i = 0; i < 2; i++) {
			read(p[0], inbuf, MSGSIZE);
			printf("Message %d read from pipe: %s \n", i, inbuf);
		}
	}

	return 0;
}
