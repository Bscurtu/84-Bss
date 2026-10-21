#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

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

int	ef_atoi(char *ptr)
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

void putStr(char *str)
{
    if (str)
        while (*str)
        {
            write(2, str, 1);
            str++;
        }
}

void error(int error)
{
    write(2, "Error while copying: ", 21);
    putStr(strerror(error));
}

int pasting(int readFd, int writeFd, char *buffer, int bufferSize)
{
    int readed;
    int pasted;
    int return_value;

    readed = 1;
    while (readed > 0)
    {
        pasted = 0;
        readed = read(readFd, buffer, bufferSize);
        if (readed > 0)
            while (pasted < readed)
            {
                return_value = write(writeFd, buffer, readed);
                if (return_value < 0)
                {
                    error(errno);
                    return (1);
                }
                pasted += return_value;
            }
    }
    return (0);
}

int check_stat(struct stat *from, struct stat *to)
{
    /* This part is new to me */
    /* Inode is the index number of a file */
    /* The st_dev is the device or partition that this files is saved in */
    /* We will create 2 structs, and use the stat function to fill the data, and then compare it to see if it matches*/
    /* Comparing the specific data of the files and where are they*/
    if (from != NULL && to != NULL)
        if (from->st_dev == to->st_dev && from->st_ino == to->st_ino)
        {
            write(2, "Input files are the same file or hardlinks\n", 44);
            return (0);
        }
    return (1);
}

int create_stat(int fd, struct stat *data)
{

    if (fd < 0)
        return (1);
    if (fstat(fd, data) < 0)
        return (1);
    return (0);
}

int check_buffer(char **argv, int *argvPos, int *bufferSize)
{
    if (ef_strcmp(argv[*argvPos], "-b") == 0)
    {
        (*argvPos)++;
        if ((*bufferSize) = ef_atoi(argv[*argvPos]), *bufferSize < 1)
        {
            write(1, "The buffer size must be a number greater than 0\n", 49);
            return (0);
        }
        (*argvPos)++;
    }
    if ((*bufferSize) == -1)
        (*bufferSize) = 65536;
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

int error_handler(char *error)
{
    while (*error && write(2, error, 1) == 1)
            error++;
    write(2, "\n", 1);
    return (1);
}

int main(int argc, char **argv)
{
	int	bufferSize;
    int readFd;
    int writeFd;
    int argvPos;
    struct stat from;
    struct stat to;
    char *buffer;

    bufferSize = -1;
    argvPos = 1;
    if (check_inputs(argc) == 0)
        return (1);
    if (check_buffer(argv, &argvPos, &bufferSize) == 0)
        return (1);

    readFd = open(argv[argvPos], O_RDONLY);
    if (readFd < 0)
        return (error_handler(strerror(errno)));
    create_stat(readFd, &from);

    argvPos++;
    if (stat(argv[argvPos], &to) >= 0)
        if (check_stat(&from, &to) == 0)
            return (error_handler(strerror(errno)));

    mode_t mode = from.st_mode & 07777;
    writeFd = open(argv[argvPos], O_CREAT | O_WRONLY | O_TRUNC, mode);
    if (writeFd < 0)
        return (error_handler(strerror(errno)));

    buffer = malloc(sizeof(char) * bufferSize + 1);
    if (!buffer)
    {
        close(readFd);
        close(writeFd);
        return (1);
    }
    if (pasting(readFd, writeFd, buffer, bufferSize) == 1)
        unlink(argv[argvPos]);
    close(readFd);
    close(writeFd);
    free(buffer);
    return (0);
}