#include "minishell.h"

static int	skip_redir(char *str, int i)
{
	char	quote;

	while (str[i] == '<' || str[i] == '>')
		i++;
	while (str[i] && is_white_space(str[i]) == 1)
		i++;
	if (isbetweenquote(str, i + 1) == 0)
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		i++;
	}
	else
	{
		while (str[i] && is_white_space(str[i]) == 0)
			i++;
	}
	return (i);
}

static int	remove_redir(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && isbetweenquote(str, i) == 1)
		{
			i = skip_redir(str, i);
			if (str[i] == '\0')
				break ;
		}
		i++;
		j++;
	}
	return (j);
}

static char	*recover_cmd(char *str)
{
	int		i;
	int		j;
	char	*cmd;

	i = remove_redir(str);
	j = 0;
	cmd = ft_calloc(i + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && isbetweenquote(str, i) == 1)
		{
			i = skip_redir(str, i);
			if (str[i] == '\0')
				break ;
		}
		cmd[j] = str[i];
		i++;
		j++;
	}
	return (cmd);
}

static int	lexer_recover(char *str, t_envir *envs, t_tabcmd *tab, char **seq)
{
	int			i;

	i = 0;
	while (seq[i])
	{
		if (lexer_2(seq, tab, str, i) == 1)
		{
			if (g_exit == 2)
			{
				ft_free_tab(envs->envi);
				free(envs);
				exit (g_exit);
			}
			return (1);
		}
		seq[i] = ft_expand(seq[i], envs);
		tab[i].cmd = recover_cmd(seq[i]);
		if (!tab[i].cmd)
		{
			ft_free_parent(tab, seq, str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	lexer(char *str, t_envir *envs)
{
	t_tabcmd	*tabcmd;
	char		**seq;

	tabcmd = init_tab(str);
	if (!tabcmd)
		return ;
	seq = ft_split_quote(str, '|');
	if (!seq)
	{
		ft_free_tabcmd(tabcmd);
		return ;
	}
	if (here_doc(str, tabcmd) == 1)
	{
		ft_free_parent(tabcmd, seq, str);
		return ;
	}
	if (lexer_recover(str, envs, tabcmd, seq) == 1)
		return ;
	ft_free_tab(seq);
	free(str);
	exec(tabcmd->nb_cmd, tabcmd, envs);
	ft_free_tabcmd(tabcmd);
}
