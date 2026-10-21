
#include "lib.h"

int open_input(const char *filename)
{
    int fd;

    if (filename == NULL || ef_strcmp(filename, "-") == 0)
        return (STDIN_FILENO);
    fd = open(filename, O_RDONLY, 644);
    if (fd < 0)
    {
        if (errno == STDIN_FILENO)
            return (STDIN_FILENO);
        else
            return (-1);
    }
    return (fd);
}