
#include "lib.h"

int parse_args(int ac, char **av, ssize_t *n_lines, int *file_index)
{
    if (ac >= 2)
        if (ef_strcmp(av[1], "-n") == 0)
        {
            line_number(ac, av, n_lines);
            *file_index = 3;
        }
        else
        {
            *file_index = 1;
            *n_lines = 10;
        }
    else
    {
        *file_index = 1;
        *n_lines = 10;
    }

    if (*n_lines < 0)
        return (-1);
    return (0);
}

ssize_t line_number(int ac, char **av, ssize_t *n_lines)
{
    if (ac < 3)
    {
        write(2, "error: a value is required for '-n <lines>' but none was supplied\n", 67);
        *n_lines = -1;
        return (-1);
    }
    if (*n_lines = ef_extract_number(av[2]), *n_lines >= 0)
        return (0);
    else
        write(2, "mtail: invalid number of lines:\n", 33);
    return (-1);
}