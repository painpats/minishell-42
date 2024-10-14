#include "minishell.h"

static void	ft_dup2(t_pipe *pipes)
{
	if (pipes->read != -1 && dup2(pipes->read, STDIN_FILENO) == -1)
		perror("dup2");
	if (pipes->write != -1 && dup2(pipes->write, STDOUT_FILENO) == -1)
		perror("dup2");
}	

int	ft_check_cmdpath(char *cmdpath, t_pipe *pipes)
{
	if (!cmdpath || ft_strncmp(cmdpath, "error", 5) == 0)
	{
		g_exit = 127;
		ft_putstr_fd("command not found\n", 2);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0],
			pipes->pfd[1]);
		return (1);
	}
	return (0);
}

void	ft_execve_error(char *path, char **split, t_envir *envs, t_tabcmd *tab)
{
	perror("execve");
	ft_free_child(path, split, envs, tab);
	exit (EXIT_FAILURE);
}

void	ft_path_error(char *path, char **split, t_envir *envs, t_tabcmd *tab)
{
	ft_free_child(path, split, envs, tab);
	exit (g_exit);
}

int	ft_child(t_tabcmd *tabcmd, t_envir *envs, t_pipe *pipes, int i)
{
	char	*cmdpath;
	char	**cmd_split;

	pipes->pid = fork();
	if (pipes->pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
		return (1);
	}
	if (pipes->pid == 0)
	{
		signal(SIGINT, &signal_child);
		ft_dup2(pipes);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
		ft_close_all_file(tabcmd[i].file, tabcmd[i].nb_file);
		tabcmd[i].cmd = ft_replace_quote(tabcmd[i].cmd);
		cmd_split = ft_stock_cmd(tabcmd[i].cmd);
		cmdpath = ft_path(tabcmd[i].cmd, envs->envi);
		if (ft_check_cmdpath(cmdpath, pipes) == 1 || !cmd_split)
			ft_path_error(cmdpath, cmd_split, envs, tabcmd);
		if (execve(cmdpath, cmd_split, envs->envi) == -1)
			ft_execve_error(cmdpath, cmd_split, envs, tabcmd);
	}
	return (0);
}
