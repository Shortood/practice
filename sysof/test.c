#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sig_handler(int num) {
    printf("\nChild Sent a signal to parent:%d\n", num);
    signal(SIGALRM, SIG_DFL);
}

int main() {
    int status;
    system("clear");
    printf("\n--------------Signal Handling Across Process---------------\n");
    swtich(fork()) {
        case -1:
            perror("\nFork Failed...\n");
            exit(1);
            break;
        case 0:
            alarm(3);
            kill(getppid(), SIGALM);
            printf("\nlts Child Process\n");
            sleep(5);
            break;
        default:
            signal(SIGALRM, sig_handler);
            wait(&status);
            printf("\nIts Parent Process\n");
            break;
    }
}