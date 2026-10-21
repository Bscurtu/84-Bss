
#include "lib.h"
int main(int ac, char **av)
{
    ssize_t n_lines;
    int file_index;
    int fd;
    int result = 0;

    parse_args(ac, av, &n_lines, &file_index);
    if (n_lines < 0)
        return (1);

    fd = open_input(av[file_index]);
    if (fd < 0)
    {
        write(2, "mtail: No such file\n", 21);
        return (1);
    }

    if (lseek(fd, 0, SEEK_CUR) == -1)
    {
        if (errno == ESPIPE)
        {
            process_stream_input(fd, n_lines);
            if (fd != 0)
                close(fd);
            return (0);
        }
        else
        {
            if (fd != 0) close(fd);
            return (1);
        }
    }
    result = print_lines(fd, read_file(fd, n_lines));
    if (fd != 0)
        close(fd);
    return (result);
}