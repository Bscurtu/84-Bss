
#include "lib.h"

void print_error()
{
	char *error = strerror(errno);
	if (!error)
		return ;
	int size = 0;
	int i = 0;

	while (error[size])
		size++;
	if (size > 0)
	{
		while (i < size)
			i += write(2, error + i, size - i);
		write(2, "\n", 1);
	}
}


int main(int ac, char **av)
{
    ssize_t n_lines;
    int file_index;
    int fd;
    int result = 0;

	if (ac == 1)
		return (1);
    parse_args(ac, av, &n_lines, &file_index);
    if (n_lines < 0)
        return (1);

    fd = open_input(av[file_index]);
    if (fd < 0)
    {
    	print_error();
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