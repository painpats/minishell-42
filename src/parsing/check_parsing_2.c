#include "minishell.h"

static int	check_redir_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>'
					&& str[i + 1] == '>')) && isbetweenquote(str, i) == 1)
		{
			i += 2;
			if (check_if_valid(str, i) == 1)
				return (1);
		}
		else if ((str[i] == '<' || str[i] == '>')
			&& isbetweenquote(str, i) == 1)
		{
			i++;
			if (check_if_valid(str, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_redir(char *str)
{
	if (check_number_redir(str) == 1)
	{
		g_exit = 2;
		printf("syntax error: wrong number of '<' or '>'\n");
		return (1);
	}
	if (check_redir_2(str) == 1)
	{
		g_exit = 2;
		return (1);
	}
	return (0);
}
