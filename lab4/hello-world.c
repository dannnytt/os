#include <stdio.h>
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

void hello(const char* str) {
    printf("hello, %s\n", str);
}

int main(int argc, char *argv[]) {
    hello(argv[1]);
}