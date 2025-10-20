#include <stdio.h>
#include <unistd.h>

// Each exec variant provides flexibility depending on use case.
// If arguments are known at compile time, execl is preferred.
// If arguments only known at run time, execv is great here.

int main(int argc, char *argv[]) {

	pid_t pid = fork();

	if (pid < 0) {
		printf("Error forking child");
	} else if (pid == 0) {
		char *myargs[2];
		myargs[0] = "/bin/ls";
		myargs[1] = NULL;
		// v prefix: takes a vector of arguments
		// p suffix: uses PATH for program
		execvp(myargs[0], myargs);
		execv(myargs[0], myargs);

		// l prefix: takes a list of arguments
		// e suffix: specify environment key value pairs for process to run in
		execl("/bin/ls", "/bin/ls");
		execle("/bin/ls", "/bin/ls");
	} else {
		printf("Parent says hello!\n");
	}
	return 0;
}


