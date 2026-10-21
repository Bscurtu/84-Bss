
#include "lib.h"

int searcher_index(const char *str, int size, off_t *offset, int n_lines)
{
    static int lines_found;

    for (int i = size - 1; i >= 0; i--)
    {
        if (str[i] == '\n')
            lines_found++;
        (*offset)++;
        if (n_lines == lines_found)
            return (1);
    }
    return (0);
}

off_t read_file(int fd, int n_lines)
{
    char buffer[BLOCK];
    off_t offset;
    off_t file_size;
    int found;
    int readed;

    found = 0;
    offset = 0;
    readed = 1;
    file_size = lseek(fd, 0, SEEK_END);
    if (file_size > BLOCK)
        lseek(fd, 0, SEEK_END);
    else
        lseek(fd, 0, 0);
    while (found == 0)
    {
        readed = read(fd, buffer, BLOCK);
        if (offset == 0)
            readed -= 1;
        found = searcher_index(buffer, readed, &offset, n_lines);
        if (lseek(fd, 0 - offset - BLOCK, SEEK_CUR) < 0|| found == 1)
            break ;
    }
    if (found == 0)
        return (file_size);
    return (offset);
}