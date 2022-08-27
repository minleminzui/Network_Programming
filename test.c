#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFE_SIZE 1024
int main() {
    int fd = open("./does_not_exist", O_RDWR | O_CREAT | O_EXCL, 0644);
    // char *message = "syscall";
    char message[BUFE_SIZE];
    sprintf(message,"syscall test");
    printf("strlen %lu  sizeof %lu\n", strlen(message), sizeof(message));
//     write(fd, message, strlen(message));
//     lseek(fd, 2, SEEK_END);
//     write(fd, message, strlen(message));
//     char buf[BUFE_SIZE];
//     lseek(fd, 0, SEEK_SET);
//     read(fd, buf, BUFE_SIZE);
//     printf("buf : %s\n", buf);
}