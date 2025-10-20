#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// If wait(*stat_loc) is called within the child process, it returns -1 (error)
// as there are no child processes to wait for
// *stat_loc is a pointer to the integer where kernal will store info
// on how the child process was terminated
// For general cases we can use NULL here as we don't care

int main (int argc, char *argv[]) {
	pid_t pid = fork();

	if (pid < 0) {
		printf("Error forking child\n");
	} else if (pid == 0) {
		printf("Child processing...\n");
		pid_t acpid = wait(NULL);
		printf("Child pid: %d\n", acpid);
	} else {
		// Child pid is returned after child process finishes, or -1 if error
		pid_t cpid = wait(NULL);
		printf("Parent processing...\n");
		printf("Child pid: %d\n", cpid);
	}

	return 0;
}
