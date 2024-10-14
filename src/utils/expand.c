#include "minishell.h"

static int	ft_simple_quote(char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			j++;
			while (str[j] != quote)
				j++;
			if (j > i)
			{
				if (quote == '\"')
					return (1);
				return (0);
			}
		}
		j++;
	}
	return (1);
}

static void	ft_fill(char *str, char *new, int j, char *name)
{
	int	k;
	int	i;

	i = -1;
	k = 0;
	while (str[++i])
		if (str[i] == '$' && ft_check(str, i) == 0
			&& ft_simple_quote(str, i) == 1)
			break ;
	i++;
	while (name[k])
	{
		k++;
		i++;
	}
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
}

static char	*ft_realloc_cmd_line(char *variable, char *str, char *name)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = -1;
	j = 0;
	k = -1;
	new = ft_calloc(ft_strlen(str) + ft_strlen(variable) - ft_strlen(name),
			sizeof(char) + 1);
	while (str[++i])
	{
		if (str[i] == '$' && ft_check(str, i) == 0
			&& ft_simple_quote(str, i) == 1)
			break ;
		new[j] = str[i];
		j++;
	}
	while (variable[++k])
	{
		new[j] = variable[k];
		j++;
	}
	ft_fill(str, new, j, name);
	return (new);
}

static char	*ft_expanding(char *str, t_envir *envs, int i)
{
	char	*variable;
	char	*name;
	char	*new;

	name = ft_recover_name(str, i);
	if (ft_strncmp(name, "?", 1) == 0)
		variable = ft_itoa(g_exit);
	else
		variable = ft_recover_variable(name, envs);
	new = ft_realloc_cmd_line(variable, str, name);
	free(name);
	free(variable);
	free (str);
	return (new);
}

char	*ft_expand(char *str, t_envir *envs)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_strdup(str);
	while (ft_strchr(new_str, '$') != NULL)
	{
		i = 0;
		while (new_str[i])
		{
			if (new_str[i] == '$' && ft_check(new_str, i) == 0
				&& ft_simple_quote(new_str, i) == 1)
				break ;
			i++;
		}
		if (new_str[i] == '\0')
			break ;
		new_str = ft_expanding(new_str, envs, i);
	}
	free(str);
	return (new_str);
}
