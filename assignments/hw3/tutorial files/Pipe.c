#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>

int main() {
    
    int fd [2]; 
    pipe(fd) ;

    pid_t pid = fork();

    if (pid < 0) {
        printf ("Fork failed. \n");
    }

    else if (pid > 0) {
        close(fd [0]);
        int fav_number = 42;
        write(fd[1], &fav_number, sizeof (fav_number));
        close(fd [1]);
    } 

    else {
        char buffer [8];
        sprintf (buffer, "%d", fd [0]);
        execlp("child", buffer, NULL);
    }

    return 0;
}