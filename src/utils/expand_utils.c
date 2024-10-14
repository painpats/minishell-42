#include "minishell.h"

static void	ft_fill_name(char *name, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && is_white_space(str[i]) == 0 && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '$')
	{
		name[j] = str[i];
		i++;
		j++;
	}
}

char	*ft_recover_name(char *str, int i)
{
	char	*name;
	int		k;
	int		j;

	i++;
	j = i;
	k = 0;
	while (str[j] && is_white_space(str[j]) == 0 && str[j] != '\"'
		&& str[j] != '\'' && str[j] != '$')
	{
		k++;
		j++;
	}
	name = ft_calloc(k + 1, sizeof(char));
	ft_fill_name(name, str, i);
	if (ft_strncmp(name, "?", 1) == 0)
	{
		free(name);
		return (ft_strdup("?"));
	}
	return (name);
}

static int	ft_find_variable(t_envir *envs, char *name)
{
	int	i;

	i = 0;
	while (envs->envi[i])
	{
		if (ft_strncmp(envs->envi[i], name, ft_strlen(name)) == 0)
			break ;
		i++;
	}
	if (ft_strlen_tab(envs->envi) == i)
		return (-1);
	return (i);
}

char	*ft_recover_variable(char *name, t_envir *envs)
{
	char	*variable;
	int		i;
	int		j;
	int		k;

	i = ft_find_variable(envs, name);
	if (i == -1)
		return (ft_strdup(""));
	j = 0;
	while (envs->envi[i][j] && envs->envi[i][j] != '=')
		j++;
	if (envs->envi[i][j] == '\0')
		return (ft_strdup(""));
	k = j;
	while (envs->envi[i][k])
		k++;
	variable = ft_calloc(k + 1, sizeof(char));
	k = 0;
	while (envs->envi[i][++j])
	{
		variable[k] = envs->envi[i][j];
		k++;
	}
	return (variable);
}

int	ft_check(char *str, int i)
{
	if (str[i + 1] != '\0' && is_white_space(str[i + 1]) == 0
		&& str[i + 1] != '\'' && str[i + 1] != '\"' && str[i + 1] != '$')
		return (0);
	return (1);
}
