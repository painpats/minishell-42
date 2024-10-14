#include "minishell.h"

static int	check_quote_2(char *str, int i, int boolean, char quote)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			boolean = 1;
			i++;
			while (str[i])
			{
				if (str[i] == quote)
				{
					boolean = 0;
					break ;
				}
				i++;
			}
			if (boolean == 1 && str[i] == '\0')
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	check_quote(char *str)
{
	int		boolean;
	int		i;
	char	quote;

	i = 0;
	boolean = 0;
	quote = '\0';
	if (check_quote_2(str, i, boolean, quote) == 1)
		return (1);
	return (0);
}

int	check_pipe(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i - 1;
		if (str[i] == '|')
		{
			while (j >= 0 && (is_white_space(str[j]) == 1
					|| isbetweenquote(str, j) == 0))
				j--;
			if (j < 0 || (str[j] == '|' && isbetweenquote(str, j) == 1))
				return (1);
			j = i + 1;
			while (str[j] && (is_white_space(str[j]) == 1
					|| isbetweenquote(str, j) == 0))
				j++;
			if (str[j] == '|' || (str[j] == '\0'
					&& isbetweenquote(str, j) == 1))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_number_redir(char *str)
{
	int		i;
	int		number;

	i = 0;
	while (str[i])
	{
		number = 0;
		while ((str[i] == '<' || str[i] == '>') && isbetweenquote(str, i) == 1)
		{
			i++;
			number++;
		}
		if (number > 2)
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

int	check_if_valid(char *str, int i)
{
	if (str[i] == '\0')
	{
		ft_putstr_fd("error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (is_white_space(str[i]) == 1)
		i++;
	if (str[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `<' or `>'\n", 2);
		return (1);
	}
	else if (str[i] == '\0')
	{
		ft_putstr_fd("error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
