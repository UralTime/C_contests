#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    pid_t pid = fork();
    if (pid < 0) {
        exit(42);
    } else if (!pid) {
        int fd = open(argv[2], O_RDONLY);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 0) < 0) {
            _exit(42);
        }
        if (close(fd) < 0) {
            _exit(42);
        }  

        fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 1) < 0) {
            _exit(42);
        }
        if (close(fd) < 0) {
            _exit(42); 
        }  

        fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 2) < 0) {
            _exit(42); 
        }
        if (close(fd) < 0) {
            _exit(42); 
        }
   
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    } else {
        int status;
        wait(&status);
        printf("%d\n", status);
    }
    return 0;
}
