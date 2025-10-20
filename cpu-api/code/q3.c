#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid = fork();
	// Prefer pid_t over int
	// Returns -1 = error, 
	// 0 in child process, 
	// child pid in parent process

	if (pid < 0) {
		printf("Error forking child");
	} else if (pid == 0) {
		printf("Child process says Hello\n");
	} else {
		sleep(1);
		printf("Parent process says Goodbye\n");
	}

	return 0;
}
