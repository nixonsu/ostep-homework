#include <stdio.h>
#include <unistd.h>

// By default every process starts with 3 standard file
// descriptors open
// STDIN_FILENO = 0 (targets keyboard)
// STDOUT_FILENO = 1 (targets screen)
// STDERR_FILENO = 2 targets screen)

// Therefore, closing the STDOUT_FILENO file descriptor
// closes standard output, meaning printf won't print
// to the screen
int main(int argc, char *argv[]) {

	pid_t pid = fork();

	if (pid < 0) {
		printf("Error forking child");
	} else if (pid == 0) {
		close(STDOUT_FILENO);
		printf("Child says hello\n");
	} else {
		printf("Parent says goodbye\n");
	}

	return 0;
}

