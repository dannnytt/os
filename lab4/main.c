#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>

int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main() {

    printf("PID родительского процесса = %d\n\n", getpid());

    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Дочерний процесс 1: PID = %d, PPID = %d\n", getpid(), getppid());
        char *args[] = {"bin/hello", "Daniel", NULL};
        execv(args[0], args);
    } 

    pid_t pid2 = fork();
    if (pid2 == 0) {
        printf("\nДочерний процесс 2: PID = %d, PPID = %d\n", getpid(), getppid());
        char *args[] = {"/bin/bash", "/home/daniel/sibsutis/acs/lab1/script.sh", NULL};
        execv(args[0], args);
    }
    getch();
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);   
    return 0;
}