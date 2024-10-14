#include "minishell.h"

static char	*create_name(void)
{
	char	*name;
	int		random;
	char	*random_suffix;

	random = 0;
	while (random < __INT_MAX__)
	{
		random_suffix = ft_itoa(random);
		name = ft_strjoin("/tmp/.mimish_", random_suffix);
		if (!name)
			return (NULL);
		free(random_suffix);
		if (access(name, F_OK) == 0)
			free(name);
		else
			break ;
		random++;
	}
	return (name);
}

static void	close_heredoc(char *name, int file, t_tabfile *tabfile, int nb_file)
{
	int	i;

	i = 0;
	close(file);
	while (i < nb_file && tabfile[i].type != 0)
		i++;
	tabfile[i].filename = ft_strdup(name);
	tabfile[i].type = HEREDOC;
	free(name);
}

int	open_heredoc(char *str, int i, t_tabfile *tabfile, int nb_file)
{
	char		*limiter;
	char		*name;
	int			file;

	name = create_name();
	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		return (1);
	limiter = recover_limiter(str, i);
	if (!limiter)
		return (1);
	if (ft_read_heredoc(limiter, file) == 1)
	{
		free(limiter);
		free(name);
		close(file);
		return (1);
	}
	if (limiter[0] != '\n')
		free(limiter);
	close_heredoc(name, file, tabfile, nb_file);
	return (0);
}

static void	ft_error_max(char **split)
{
	ft_putstr_fd("maximum here-document count exceeded\n", 2);
	g_exit = 2;
	ft_free_tab(split);
}

int	here_doc(char *str, t_tabcmd *tabcmd)
{
	int		boolean;
	int		i;
	char	**split;

	split = ft_split_quote(str, '|');
	i = 0;
	while (split[i])
	{
		boolean = check_if_here_doc(split[i]);
		if (boolean == 1)
		{
			ft_error_max(split);
			return (g_exit);
		}
		else if (boolean != 2 && boolean != 1)
		{
			signal(SIGINT, &ctrl_c_heredoc);
			if (ft_heredoc_2(split[i], tabcmd) == 1)
				return (ft_free_tab(split), 1);
		}
		i++;
	}
	ft_free_tab(split);
	return (0);
}
