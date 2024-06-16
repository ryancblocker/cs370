#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int isDivisible(int divisor, int dividend) {
    //divide by 0
    if (dividend == 0) {
        return 0;
    }

    if (divisor % dividend == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Checker: Your arguments must be given as <divisor> <dividend>\n");
        exit(1);
    }

    pid_t pid = getpid();

    printf("Starting process [%d]\n", pid);

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);

    if (isDivisible(divisor, dividend)) {
        printf("Checker: %d is divisible by %d.\n", divisor, dividend);
        printf("Checker: [%d] returned: 1\n", pid);
        return 1;
    } else {
        printf("Checker: %d is not divisible by %d.\n", divisor, dividend);
        printf("Checker: [%d] returned: 0\n", pid);
        return 0;
    }
    return 0;
}
