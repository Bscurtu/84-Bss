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
			return ((int) *str1 - (int) *str2);
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

void ef_error(int index, int error, char *filename)
{
	if (index != 1)
		write(1, "\n", 1);
	write(2, "mcat: ", 6);
	ef_putstr(filename);
	if (error == 1)
		write(2, ": No such file or directory\n", 28);
	if (error == 2)
		write(2, ": Is a directory\n", 18);
}

void et_fileIteration(int index, int argc, char **argv, int *returned)
{
	char buffer[100];
	int actual_fd;
	int readed;

	for (;index < argc; index++)
	{
		if (ef_strcmp(argv[index], "-") == 0)
		{
			readed = 1;
				while (readed > 0)
				{
					readed = read(0, &buffer, 100);
					if (readed > 0)
						write(1, &buffer, readed);
				}
			}
			else
			{
				actual_fd = open(argv[index], O_RDONLY);
				if (actual_fd < 0)
				{
					*returned = 1;
					ef_error(index, 1, argv[index]);
				}
				else
				{
					readed = 1;
					while (readed > 0)
					{
						readed = read(actual_fd, &buffer, 100);
						if (readed == -1 && errno == EISDIR)
						{
							*returned = 1;
							ef_error(index, 2, argv[index]);
							break ;
						}
						write(1, &buffer, readed);
					}
				}
				if (actual_fd > 0)
					close(actual_fd);
			}
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
			readed = read(0, &buffer, 100);
			write(1, &buffer, readed);
		}
	}
	else
		et_fileIteration(index, argc, argv, &returned);
	return (returned);
}