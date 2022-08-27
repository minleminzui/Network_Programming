#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void timeout(int sig) {
    if (sig == SIGALRM) {
        fputs("简单字符串\n", stdout);
        alarm(1);
    }
}

void ctrl_hanlder(int sig) {
    if (sig == SIGINT) {
        fputs("你想要退出吗？\n",stdout);
        char c;
        scanf("%c", &c);
        if (c == 'y' || c == 'Y') {
            _exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    struct sigaction act1, act2;
    act1.sa_flags = 0;
    sigemptyset(&act1.sa_mask);
    act1.sa_handler = timeout;
    sigaction(SIGALRM, &act1, 0);

    act2.sa_flags = 0;
    sigemptyset(&act2.sa_mask);
    act2.sa_handler = ctrl_hanlder;
    sigaction(SIGINT, &act2, 0);

    alarm(1);

    while (1)
    {
        sleep(5);
    }
    

    return 0;
}