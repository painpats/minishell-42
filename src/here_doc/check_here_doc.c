#include "minishell.h"

int	check_if_here_doc(char *str)
{
	int	i;
	int	chevron;
	int	here_doc;

	i = 0;
	here_doc = 0;
	while (str[i])
	{
		chevron = 0;
		while (str[i] && str[i] == '<')
		{
			chevron++;
			i++;
		}
		if (chevron == 2)
			here_doc++;
		if (str[i])
			i++;
	}
	if (here_doc > 16)
		return (1);
	else if (here_doc == 0)
		return (2);
	return (0);
}

int	ft_heredoc_2(char *str, t_tabcmd *tabcmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && isbetweenquote(str, i) == 1)
		{
			if (open_heredoc(str, i, tabcmd[j].file, tabcmd[j].nb_file) == 1)
				return (1);
		}
		if (str[i] == '|')
			j++;
		i++;
	}
	return (0);
}
