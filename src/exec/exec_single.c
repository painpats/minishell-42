#include "minishell.h"

void	exec_single_builtins(t_tabcmd *tabcmd, t_pipe *pipes, t_envir *envs)
{
	int	savestdin;
	int	savestdout;

	savestdin = dup(STDIN_FILENO);
	savestdout = dup(STDOUT_FILENO);
	if (pipes->read >= 0 && dup2(pipes->read, STDIN_FILENO) == -1)
		perror("dup2");
	if (pipes->write >= 0 && dup2(pipes->write, STDOUT_FILENO) == -1)
		perror("dup2");
	ft_builtins(tabcmd, envs);
	if (pipes->read >= 0 && dup2(savestdin, STDIN_FILENO) == -1)
		perror("dup2");
	if (pipes->write >= 0 && dup2(savestdout, STDOUT_FILENO) == -1)
		perror("dup2");
	if (ft_strncmp_without_ws("exit", tabcmd->cmd, 4) == 0)
	{
		ft_close_fd(savestdin, savestdout, -1, -1);
		pipes->pfd[0] = -1;
		pipes->pfd[1] = -1;
		ft_exit(tabcmd, pipes, envs, 0);
		ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
	}
	ft_close_fd(pipes->read, pipes->write, savestdin, savestdout);
	ft_close_all_file(tabcmd->file, tabcmd->nb_file);
}
