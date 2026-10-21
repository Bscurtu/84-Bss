
#include "lib.h"

int set_lseek(int fd, off_t offset, off_t *size_from)
{
    *size_from = lseek(fd, 0, SEEK_END);
    return (lseek(fd, (*size_from) - offset, SEEK_SET));
}

int print_lines(int fd, off_t offset)
{
    int readed;
    int wrote;
    off_t size_from;
    char buffer[4096];

    if (set_lseek(fd, offset, &size_from) < 0)
        return (1);
    readed = 1;
    wrote = 0;
    while (readed > 0)
    {
        readed = read(fd, buffer, 4096);
        wrote = 0;
        while (wrote < readed)
            wrote = write(1, buffer, readed);
    }
    return (0);
}