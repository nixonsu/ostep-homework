#include <stdio.h>
#include <unistd.h>

// When child process sets x to 50, it still remains as 100 in the parent process, 
// implying that each process has its own copy of the variable x.
int main(int argc, char *argv[]) {
    int x = 100;

    printf("Value of x: %d\n", x);

    int rc = fork();

    printf("Value of x: %d\n", x);

    x = 50;

    printf("Value of x: %d\n", x);
    
    return 0;
}
