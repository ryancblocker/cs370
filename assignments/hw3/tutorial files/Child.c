#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

int main(int arg, char** argv) {

    int fd = atoi (argv [0]);
    int fav_number = atoi (argv [0]);
    
    read (fd, &fav_number, sizeof (fav_number)) ;
    printf("Input from pipe: ed\n", fav_number);
    
    return 0;
}