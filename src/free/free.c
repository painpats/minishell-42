#include "minishell.h"

void	ft_free_tabfile(t_tabcmd tab)
{
	int	i;

	i = 0;
	while (i < tab.nb_file)
	{
		if (tab.file[i].type == HEREDOC)
			unlink(tab.file[i].filename);
		if (tab.file[i].fd != -1)
			close(tab.file[i].fd);
		free(tab.file[i].filename);
		i++;
	}
	free(tab.file);
}

void	ft_free_tabcmd(t_tabcmd *tab)
{
	int	i;
	int	nbcmd;

	i = 0;
	nbcmd = tab[i].nb_cmd;
	while (i < nbcmd)
	{
		free(tab[i].cmd);
		ft_free_tabfile(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_exit(t_tabcmd *tab, t_envir *envs, char **str, t_pipe *pipes)
{
	ft_free_tab(envs->envi);
	free(envs);
	ft_free_tab(str);
	ft_free_tabcmd(tab);
	ft_close_fd(pipes->read, pipes->write, pipes->pfd[0], pipes->pfd[1]);
}
