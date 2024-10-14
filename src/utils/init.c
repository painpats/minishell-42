#include "minishell.h"

int	number_file(char *str, int cmd)
{
	char	**split_str;
	int		i;
	int		number_file;

	number_file = 0;
	i = 0;
	split_str = ft_split_quote(str, '|');
	while (split_str[cmd][i])
	{
		if (((split_str[cmd][i] == '<' && split_str[cmd][i + 1] == '<') ||
			(split_str[cmd][i] == '>' && split_str[cmd][i + 1] == '>')) &&
			isbetweenquote(split_str[cmd], i) == 1)
		{
			i++;
			number_file++;
		}
		else if ((split_str[cmd][i] == '<' || split_str[cmd][i] == '>') &&
			isbetweenquote(split_str[cmd], i) == 1)
			number_file++;
		i++;
	}
	ft_free_tab(split_str);
	return (number_file);
}

int	number_cmd(char *str)
{
	int	i;
	int	number_cmd;

	i = 0;
	number_cmd = 1;
	while (str[i])
	{
		if (str[i] == '|' && isbetweenquote(str, i) == 1)
			number_cmd++;
		i++;
	}
	return (number_cmd);
}

static void	init_tabfile(t_tabcmd *tabcmd, int i, char *str)
{
	int	j;

	j = 0;
	while (j < number_file(str, i))
	{
		tabcmd[i].file[j].fd = -1;
		tabcmd[i].file[j].type = 0;
		tabcmd[i].file[j].filename = NULL;
		j++;
	}
}

t_tabcmd	*init_tab(char *str)
{
	t_tabcmd	*tabcmd;
	int			i;

	i = 0;
	tabcmd = malloc(sizeof(t_tabcmd) * number_cmd(str) + 1);
	if (!tabcmd)
		return (NULL);
	while (i < number_cmd(str))
	{
		tabcmd[i].cmd = NULL;
		tabcmd[i].file = malloc(sizeof(t_tabfile)
				* number_file(str, i));
		tabcmd[i].nb_file = number_file(str, i);
		tabcmd[i].nb_cmd = number_cmd(str);
		if (!tabcmd[i].file)
		{
			free(tabcmd);
			return (NULL);
		}
		init_tabfile(tabcmd, i, str);
		i++;
	}
	return (tabcmd);
}
