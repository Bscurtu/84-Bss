#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int	ef_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return ((unsigned char) *str1 - (unsigned char) *str2);
		}
		str2++;
		str1++;
	}
	return ((int) *str1 - (int) *str2);
}

void ef_putstr(char *str)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
}

void ef_error(int error, char *filename)
{
	write(2, "mcat: ", 6);
	ef_putstr(filename);
	write(2, ": ", 2);
	ef_putstr(strerror(error));
}

int copy_fd(int fd, char *buffer, int buffer_size, int *returned, int *error)
{
    int n;

    while ((n = read(fd, buffer, buffer_size)) > 0)
    {
		if (write(1, buffer, n) != n)
		{
			*error = errno;
			*returned = 1;
			return (-1);
		}
	}
	if (n < 0)
	{
		*error = errno;
		*returned = 1;
		return (-1);
	}
	return (0);
}

void ef_fileIteration(int index, int argc, char **argv, int *returned)
{
	char buffer[4096];
	int actual_fd;
	int error;

	for (;index < argc; index++)
	{
		actual_fd = -1;
		if (ef_strcmp(argv[index], "-") == 0)
			copy_fd(0, buffer, 100, returned, &error);
		else
		{
			actual_fd = open(argv[index], O_RDONLY);
			if (actual_fd < 0)
			{
				error = errno;
				ef_error(error, argv[index]);
				*returned = 1;
			}
			else
			{
				if (copy_fd(actual_fd, buffer, 4096, returned, &error) == -1)
					ef_error(error, argv[index]);
			}
		}
		if (actual_fd >= 2)
			close(actual_fd);
	}
}

int main(int argc, char **argv)
{
	int	index;
	char buffer[100];
	int	returned;
	int	readed;

	index = 1;
	returned = 0;
	if (argc < 2)
	{
		readed = 1;
		while (readed > 0)
		{
			readed = read(0, buffer, 100);
			if (readed > 0)
				write(1, &buffer, readed);
		}
	}
	else
		ef_fileIteration(index, argc, argv, &returned);
	return (returned);
}