#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <stdlib.h>
#include <errno.h>


int main()
{
    pid_t pid;
    int rv;
    int status;
    
    switch(pid = fork()) {
        case -1:
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        case 0:
            printf(" CHILD: Это процесс-потомок!\n");
            printf(" CHILD: PID -- %d\n", getpid());
            printf(" CHILD: PID родителя -- %d\n", getppid());
            printf(" CHILD: Введите мой код возврата (как можно меньше):");
            scanf("%d", &rv);
            printf(" CHILD: Выход!\n");
            exit(rv);
        default:
            printf("PARENT: Это процесс-родитель!\n");
            printf("PARENT: PID -- %d\n", getpid());
            printf("PARENT: PID потомка %d\n",pid);
            printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
            waitpid(pid, &status, 0);

            // Получаем и выводим код возврата дочернего процесса
            if (WIFEXITED(status)) {
                printf("PARENT: Код возврата потомка: %d\n", WEXITSTATUS(status));
            } else {
                printf("PARENT: Потомок завершился некорректно.\n");
            }

            printf("PARENT: Выход!\n");
    }
}