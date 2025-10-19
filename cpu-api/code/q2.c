#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

// When both parent and child process write to the same file descriptor concurrently,
// their outputs may interleave in the file due to context switching. Both processes have access to
// the same file descriptor.
int main(int argc, char *argv[]) {

    // File descriptors are integers that uniquely identify an opened file within a process.
    // Here, we open a file named "output.txt" for writing with fd = 3 (0,1,2 are reserved for stdin, stdout, stderr).
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // These arguments are used for opening the file for writing.

    printf("File descriptor: %d\n", fd);

    int pid = fork();

    if (pid == 0) {
        // Child process
        for (int i = 0; i < 10; i++) {
            dprintf(fd, "Child writing line %d\n", i);
            usleep(100000); // Sleep 0.1s, IO task and CPU swaps to other process.
        }
    } else {
        // Parent process
        for (int i = 0; i < 10; i++) {
            dprintf(fd, "Parent writing line %d\n", i);
            usleep(100000); // Sleep 0.1s, IO task and CPU swaps to other process.
        }
    }

    close(fd);

    return 0;
}

