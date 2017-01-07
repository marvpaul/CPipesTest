#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ZEICHEN 32

int main() {
    int fd[2], i, n;
    pid_t pid;
    char zeile[MAX_ZEICHEN];


    pipe(fd); //Create a pipe

    pid = fork(); // Fork programm
    if(pid > 0){
        printf("Hello, I am the parent process process. I've waited. ");
        close(fd[1]);
        n = read(fd[0], zeile, MAX_ZEICHEN);
        for(int i = 0; i < n; i++){
            zeile[i] = toupper(zeile[i]);
        }
        write(STDOUT_FILENO, zeile, n);

    } else{
        close(fd[0]);
        printf("Hello! I am the child process. Why does my parent process wait for me?");
        fgets(zeile, MAX_ZEICHEN, stdin);
        write(fd[1], zeile, strlen(zeile));
    }
    exit(0);
}