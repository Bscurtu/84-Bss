
#include "run.h"

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

static int create_command(char *command[], int ac, char **av)
{
	int i;

	for (i = 0; i < ac - 1; i++)
	{
		command[i] = av[i + 1];
	}
	command[i] = NULL;
	return (1);
}

static int print_command(int returned, struct rusage resources)
{
	if (WIFEXITED(returned) == 1)
	{
		if (WEXITSTATUS(returned) == 0)
			printf("[run] exited with status: %i · %li.%lis real · %li.%li MiB max RSS\n", WEXITSTATUS(returned), resources.ru_stime.tv_sec + resources.ru_utime.tv_sec, resources.ru_stime.tv_usec + resources.ru_stime.tv_usec, resources.ru_maxrss / 1024, resources.ru_maxrss % 1024);
		else
		{
			printf("[run] %s\n", strerror(WEXITSTATUS(returned)));
			if (WEXITSTATUS(returned) == 2)
				return (127);
			if (WEXITSTATUS(returned) == 8)
				return (126);
			else
				return (WEXITSTATUS(returned));
		}
	}
	else
	{
		printf("[run] killed by signal %i %s %s · %li.%lis real · %li.%li MiB max RSS\n", WTERMSIG(returned), strsignal(WTERMSIG(returned)), WCOREDUMP(returned) == 0 ? "" : "core dumped", resources.ru_stime.tv_sec + resources.ru_utime.tv_sec, resources.ru_stime.tv_usec + resources.ru_stime.tv_usec, resources.ru_maxrss / 1024, resources.ru_maxrss % 1024);
		return (128 + WTERMSIG(returned));
	}

	return (0);
}

static int run_command(char **command, int ac, char **av)
{
	char	*d_path;
	char	*tmp;
	pid_t	pid;
	char	**path_list;
	int 	returned = 0;
	struct rusage resources;
	
	create_command(command, ac, av);
	pid = fork();
	if (pid == 0)
	{
		if (is_search(av[1]) == 0)
		{
			execve(av[1], command, NULL);
			exit(errno);
		}
		else
		{
			int value = 0;

			path_list = ft_split(getenv("PATH"), ':');
			if (path_list == NULL)
			{}
			for (int i = 0; path_list[i]; i++)
			{
				tmp = ft_strjoin("/", av[1]);
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
	}
	else if (pid > 0)
		wait4(pid, &returned, 0, &resources);
	return (print_command(returned, resources));
}

int main(int ac, char **av)
{
	char	*command[ac];

	if (ac <= 1)
		return (1);
	return(run_command(command, ac, av));
}