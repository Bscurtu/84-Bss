
#include "pipeline.h"

static int is_search(char *str)
{
	while (*str)
	{
		if (*str == '/')
		return (0);
		str++;
	}
	return (1);
}

int run_command(char **command, int pipe_fd[2], int before_fd, int is_last, int is_first)
{
	char	*d_path;
	char	*tmp;
	char	**path_list;

	if (is_first == 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	if (is_first == 0 && is_last == 0)
	{
		dup2(before_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	if (is_last == 1)
	{
		dup2(before_fd, STDIN_FILENO);
	}

	close(pipe_fd[0]);
    close(pipe_fd[1]);

    if (before_fd != -1)
		close(before_fd);

	if (is_search(command[0]) == 0)
	{
		execve(command[0], command, NULL);
		exit(errno);
	}
	else
	{
		int value = 0;
		path_list = ft_split(getenv("PATH"), ':');

		if (path_list == NULL){}

		for (int i = 0; path_list[i]; i++)
		{
			tmp = ft_strjoin("/", command[0]);
			d_path = ft_strjoin(path_list[i], tmp);

			if (execve(d_path, command, NULL) == -1)
				value = errno;
			free(path_list[i]);
			free(tmp);
			free(d_path);
		}
		free(path_list);
		exit(value);
	}
	return (1);
}
