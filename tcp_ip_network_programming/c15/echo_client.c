#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in ser_adr;
    FILE *readfp;
    FILE *writefp;
    if (argc != 3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }
    memset(&ser_adr, 0, sizeof(ser_adr));
    ser_adr.sin_family = AF_INET;
    ser_adr.sin_addr.s_addr = inet_addr(argv[1]);
    ser_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&ser_adr, sizeof(ser_adr)) == -1) {
        error_handling("connected error");
    } else {
        puts("Connected.....");
    }

    readfp = fdopen(sock, "r");
    writefp = fdopen(sock, "w");

    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        fputs(message, writefp);
        fflush(writefp);
        fgets(message, BUF_SIZE, readfp);
        printf("Message from server: %s\n", message);
    }
    fclose(readfp);
    fclose(writefp);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}