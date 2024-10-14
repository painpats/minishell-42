#include "minishell.h"

static int	ft_isvalid_export(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (0);
	return (1);
}

int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i])
	{
		if (arg[i] == '=' || (arg[i] == '+' && arg[i + 1] == '='))
			break ;
		if (ft_isvalid_export(arg[i]) == 1)
		{
			printf("export: `%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	if (i == 0)
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

int	check_if_already_in_env(t_envir *envs, char *name)
{
	int	i;
	int	j;

	i = ft_strlen(name);
	j = 0;
	while (envs->envi[j])
	{
		if (ft_strncmp(envs->envi[j], name, i) == 0)
			return (1);
		j++;
	}
	return (0);
}

int	ft_count(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		j++;
		i++;
	}
	return (j);
}
