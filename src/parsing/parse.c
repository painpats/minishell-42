#include "minishell.h"

static int	syntax_check(char *str)
{
	if (check_quote(str) == 1)
	{
		g_exit = 2;
		ft_putstr_fd("syntax error: quote not close\n", 2);
		return (1);
	}
	if (check_pipe(str) == 1)
	{
		g_exit = 2;
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	if (check_redir(str) == 1)
		return (1);
	return (0);
}

int	ft_isvalid(char c)
{
	if (c == '.' || c == '/' || c == '[')
		return (1);
	return (0);
}

int	ft_check_input(char *str)
{
	if (ft_strlen(str) == 1 && ft_isvalid(str[0]) == 1)
	{
		ft_putstr_fd("command not found\n", 2);
		g_exit = 127;
		return (1);
	}
	return (0);
}

void	parse(char *str, t_envir *envs)
{
	if (!str[0] || !str)
		return ;
	if (ft_check_input(str) == 1)
		return ;
	if (syntax_check(str) == 1)
	{
		free(str);
		return ;
	}
	lexer(str, envs);
}
