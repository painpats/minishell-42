#include "minishell.h"

static void	waitcustom(int boolean, t_pipe *pipes)
{
	int	status;

	if (boolean == 0)
	{
		ft_close_fd(pipes->pfd[0], pipes->pfd[1], pipes->read, pipes->write);
		return ;
	}
	waitpid(pipes->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	ft_close_fd(pipes->pfd[0], pipes->pfd[1], pipes->read, pipes->write);
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
}

static int	exec_3(t_tabcmd *tabcmd, int nb_cmd, t_pipe *pipes, int i)
{
	open_file(tabcmd[i], pipes);
	if (pipes->write == -1 && i + 1 >= nb_cmd)
		pipes->write = -1;
	else if (pipes->write == -1)
		pipes->write = pipes->pfd[1];
	else
		close(pipes->pfd[1]);
	return (0);
}

static int	exec_2(t_tabcmd *tabcmd, t_envir *envs, t_pipe *pipes, int i)
{	
	int	boolean;

	while (++i < tabcmd->nb_cmd)
	{
		boolean = 0;
		if (pipe(pipes->pfd) == -1)
			exit (EXIT_FAILURE);
		if (exec_3(tabcmd, tabcmd->nb_cmd, pipes, i) == 0)
		{
			if (is_builtins(tabcmd[i].cmd) == 1)
			{
				if (ft_child_builtins(tabcmd, envs, pipes, i) == 1)
					return (1);
			}
			else if (ft_child(tabcmd, envs, pipes, i) == 1)
				return (1);
			ft_close_fd(pipes->read, pipes->write, -1, -1);
			pipes->read = pipes->pfd[0];
			boolean = 1;
		}
	}
	waitcustom(boolean, pipes);
	return (0);
}

static int	check_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_white_space(str[i]) == 1)
	{
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	exec(int nb_cmd, t_tabcmd *tabcmd, t_envir *envs)
{
	t_pipe	pipes;
	int		i;

	pipes.read = -1;
	i = -1;
	if (check_cmd(tabcmd->cmd) == 1)
		return (1);
	signal(SIGINT, signal_child);
	signal(SIGQUIT, signal_child);
	if (nb_cmd == 1 && is_builtins(tabcmd[0].cmd) == 1)
	{
		if (open_file(tabcmd[0], &pipes) == 0)
			exec_single_builtins(tabcmd, &pipes, envs);
		return (0);
	}
	if (exec_2(tabcmd, envs, &pipes, i) == 1)
		return (1);
	ft_close_fd(pipes.read, pipes.write, pipes.pfd[0], pipes.pfd[1]);
	return (0);
}
