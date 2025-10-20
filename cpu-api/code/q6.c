
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Using waitpid(pid_t pid) allows one to specify the exact PID to wait for
// Useful for scenarios where there are multiple child forks
// And a specific child process needs to be waited on

int main (int argc, char *argv[]) {
	pid_t pid = fork();

	if (pid < 0) {
		printf("Error forking child\n");
	} else if (pid == 0) {
		printf("Child processing...\n");
	} else {
		// Child pid is returned after child process finishes, or -1 if error
		pid_t cpid = waitpid(pid, NULL, 0);
		printf("Parent processing...\n");
		printf("Child pid: %d\n", cpid);
	}

	return 0;
}
