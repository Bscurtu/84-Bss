
#include "pipeline.h"

int main(int ac, char **av)
{
	char **this_command;
	pid_t pid;
	int	pipe_fd[2];
	int	before_fd = -1;
	int j = 0;

	pid = getpid();
	for (int i = 1; i < ac; i++)
	{
		this_command = ft_split(av[i], ' ');
		for (j = 0; this_command[j] != NULL; j++) {};
		pipe(pipe_fd);
		pid = fork();
		
		if (pid == 0)
		{
			run_command(this_command, pipe_fd, before_fd, i == ac - 1, i == 1);
			for (; j >= 0; j--)
				free(this_command[j]);
			free(this_command);
			exit (0);
		}
		else
		{
			for (; j >= 0; j--)
				free(this_command[j]);
			free(this_command);
			
			close(pipe_fd[1]);
			if (before_fd != -1)
				close(before_fd);
			before_fd = pipe_fd[0];
		}
	}
	while (wait(NULL) > 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(before_fd);
	return (0);
}