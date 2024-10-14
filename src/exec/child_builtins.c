#include "minishell.h"

static void	ft_dup2(t_pipe *pipes)
{
	if (pipes->read >= 0 && dup2(pipes->read, STDIN_FILENO) == -1)
		perror("dup2");
	if (pipes->write >= 0 && dup2(pipes->write, STDOUT_FILENO) == -1)
		perror("dup2");
}

static void	ft_exit_child(t_tabcmd *tabcmd, t_envir *envs, t_pipe *pipes, int i)
{
	ft_exit(tabcmd, pipes, envs, i);
	ft_close_fd(pipes->read, pipes->write, pipes->pfd[0],
		pipes->pfd[1]);
	ft_free_tabcmd(tabcmd);
	ft_free_tab(envs->envi);
	free(envs);
	exit (g_exit);
}

int	ft_child_builtins(t_tabcmd *tabcmd, t_envir *envs, t_pipe *pipes, int i)
{
	pipes->pid = fork();
	if (pipes->pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
		return (1);
	}
	if (pipes->pid == 0)
	{
		ft_dup2(pipes);
		ft_close_all_file(tabcmd->file, tabcmd->nb_file);
		ft_builtins(&tabcmd[i], envs);
		if (ft_strncmp_without_ws("exit", tabcmd[i].cmd, 4) == 0)
			ft_exit_child(tabcmd, envs, pipes, i);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
		ft_free_tabcmd(tabcmd);
		ft_free_tab(envs->envi);
		free(envs);
		exit (0);
	}
	return (0);
}
