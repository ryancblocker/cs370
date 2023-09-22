#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    //error checking for arguments
    if (argc != 6) {
        printf("Coordinator: You must give your arguments like <divisor> <dividend1> <dividend2> <dividend3> <dividend4>\n");
        exit(1);
    }

    //convert arguments to integers
    int divisor = atoi(argv[1]);
    int dividends[4];
    for (int i = 0; i < 4; i++) {
        dividends[i] = atoi(argv[i + 2]);
    }

    //Testing process start/end
    printf("Coordinator: Parent Process Starts\n");

    // Fork and run the checker program for each dividend
    for (int i = 0; i < 4; i++) {
        
        pid_t child_pid = fork();

        //printf("Coordinator: forked process with ID %d\n", child_pid);

        if (child_pid == -1) {
            printf("Coordinator: Fork failed\n");
            exit(1); // Exit with an error code
        }

        if (child_pid == 0) {

            //convert divisor and dividends to strings so I can pass as an argument
            char divisorString[20];
            char dividendString[20];

            snprintf(divisorString, sizeof(divisorString), "%d", divisor);
            snprintf(dividendString, sizeof(dividendString), "%d", dividends[i]);

            //change to child process + args
            execlp("./checker", "./checker", divisorString, dividendString, NULL);

            //exec fail check
            printf("Coordinator: execlp failed\n");
            exit(1);
        }

        int status;
        for (int i = 0; i < 4; i++) {  
            wait(&status);
        }
        printf("Parent Process waiting...\n");
    }
    
    //parent ends
    printf("Coordinator: Parent Process Ends\n"); 
    return 0;
}
