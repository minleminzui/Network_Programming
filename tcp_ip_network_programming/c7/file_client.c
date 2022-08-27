#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in sock_addr;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("receive.dat", "wb");
    sd = socket(PF_INET, SOCK_STREAM, 0);

    if (sd == -1) {
        error_handling("socket() error!");
    }

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) {
        error_handling("connect() error!");
    }
    
    while ((read_cnt = read(sd, buf, BUF_SIZE)) != 0) {
        fwrite(buf, 1, read_cnt, fp);
    }

    puts("Received file data");
    write(sd, "Thank you", 10);
    fclose(fp); close(sd);

    return 0;
}

void error_handling(char *messgae) {
    fputs(messgae, stderr);
    fputc('\n', stderr);
    exit(1);
}