
#include "family.h"

int ef_atoi(char *str)
{
    long number;

    number = 0;
    if (!str)
        return (-1);
    if (!(*str >= '0' && *str <= '9'))
        return (-1);
    while (*str && *str >= '0' && *str <= '9')
    {
        number *= 10;
        number += *str - '0';
        if (number > INT_MAX)
            return (-1);
        str++;
    }
    return (number);
}

int check_input(int ac, char *n)
{
    if (ac < 2)
        return (-1);
    return (ef_atoi(n));
}

int main(int ac, char **av)
{
    int n;
    pid_t pid;
    pid_t p_pid;
    int returned;

    pid = getpid();
    if ((n = check_input(ac, av[1])) < 0)
        return (-1);
    p_pid = getppid();
    printf("Original pid: %d\n", p_pid);

    printf("Hello");
    for (int i = 0; i < n; ++i)
    {
        pid = fork();
        if (pid > 0)
        {
            waitpid(pid, &returned, 0);
            printf("Stopped: %d, with code %i\n", pid,  WEXITSTATUS(returned));
        }
        else if (pid == 0)
        {
            pid = getpid();
            p_pid = getppid();
            printf("My pid: %d, Father pid: %d\n", pid, p_pid);
            sleep(i);
            exit(i);
        }
        else
        {
            printf("fork error\n");
            exit(1);
        }
    }
    return (0);
}