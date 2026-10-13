#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

int	et_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return ((int) *str1 - (int) *str2);
		}
		str2++;
		str1++;
	}
	return ((int) *str1 - (int) *str2);
}

int	et_atoi(char *ptr)
{
	int	total;

	total = 0;
	if (*ptr == '-')
	{
		return (-1);
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		total *= 10;
		total += *ptr - '0';
		ptr++;
	}
	return (total);
}

void pasting(int read_fd, int write_fd, char *buffer, int buffer_size)
{
    int readed;

    readed = 1;
    while (readed > 0)
    {
        readed = read(read_fd, buffer, buffer_size);
        if (readed > 0)
            write(write_fd, buffer, readed);
    }
}

int check_stat(char **argv, int pos)
{
    /* This part is new to me */
    /* Inode is the index number of a file */
    /* The st_dev is the device or partition that this files is saved in */
    /* We will create 2 structs, and use the stat function to fill the data, and then compare it to see if it matches*/
    struct stat from;
    struct stat to;
    stat(argv[pos], &from);
    stat(argv[pos + 1], &to);
    /* Comparing the specific data of the files and where are they*/
    if (from.st_dev == to.st_dev && from.st_ino == to.st_ino)
    {
        write(1, "Input files are the same file or hardlinks\n", 44);
        return (0);
    }
    return (1);
}

int check_buffer(char **argv, int *argv_pos, int *buffer_size)
{
    if (et_strcmp(argv[*argv_pos], "-b") == 0)
    {
        (*argv_pos)++;
        if ((*buffer_size) = et_atoi(argv[*argv_pos]), *buffer_size < 1)
        {
            write(1, "The buffer size must be a number greater than 0\n", 49);
            return (0);
        }
        (*argv_pos)++;
    }
    if ((*buffer_size) == -1)
        (*buffer_size) = 65536;
    return (1);
}


int check_inputs(int argc)
{
    if (argc != 3 && argc != 5)
    {
        write(1, "Invalid number of arguments\n", 29);
        return (0);
    }
    return (1);
}

int main(int argc, char **argv)
{
	int	buffer_size;
    int read_fd;
    int write_fd;
    int argv_pos;
    char *buffer;
    buffer_size = -1;
    argv_pos = 1;
    if (check_inputs(argc) == 0)
        return (0);
    if (check_buffer(argv, &argv_pos, &buffer_size) == 0)
        return (0);
    if (check_stat(argv, argv_pos) == 0)
        return (0);
    buffer = malloc(sizeof(char) * buffer_size + 1);
    if (!buffer)
        return (1);
    
    read_fd = open(argv[argv_pos], O_RDONLY, 0);
    argv_pos++;
    write_fd = open(argv[argv_pos], O_CREAT | O_RDWR, 0);
    if (read_fd < 0 || write_fd < 0)
    {
        if (read_fd > 0)
            close(read_fd);
        if (write_fd > 0)
            close(write_fd);
        free(buffer);
        return (0);
    }
    pasting(read_fd, write_fd, buffer, buffer_size);
    close(read_fd);
    close(write_fd);
    free(buffer);
    return (1);
}