#include "minishell.h"

void	ft_export_arg(char *str, t_envir *envs)
{
	int		i;
	int		j;
	char	*name_element;

	i = 0;
	while (str[i] != '=')
		i++;
	name_element = ft_calloc(i + 1, sizeof(char));
	j = 0;
	while (str[j] != '=')
	{
		if (str[j] == '+' && str[j + 1] == '=')
			break ;
		name_element[j] = str[j];
		j++;
	}
	if (check_if_already_in_env(envs, name_element) == 0)
		ft_export_create_line(str, envs, name_element, i + 1);
	else if (str[i - 1] != '+'
		&& check_if_already_in_env(envs, name_element) == 1)
		ft_export_del_to_create(str, envs, i + 1, name_element);
	else
		ft_export_append(name_element, str, i + 1, envs);
}

void	ft_export_del_to_create(char *str, t_envir *envs, int start, char *name)
{
	int	i;

	i = 0;
	while (envs->envi[i])
	{
		if (ft_strncmp(envs->envi[i], name, ft_strlen(name)) == 0)
			break ;
		i++;
	}
	envs->envi = ft_realloc(envs->envi, i);
	ft_export_create_line(str, envs, name, start);
}

void	ft_export_add_env(t_envir *envs, char *line)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (envs->envi[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (envs->envi[i])
	{
		new_tab[i] = ft_strdup(envs->envi[i]);
		i++;
	}
	new_tab[i] = ft_strdup(line);
	ft_free_tab(envs->envi);
	free(line);
	envs->envi = new_tab;
}

char	**ft_realloc(char **tab, int pull)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
		i++;
	if (i == 0)
		return (ft_free_tab(tab), NULL);
	new_tab = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (i != pull)
		{
			new_tab[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	ft_free_tab(tab);
	return (new_tab);
}

void	ft_print_export_quote(char *str)
{
	int	i;
	int	boolean;

	i = 0;
	boolean = 0;
	printf("declare -x ");
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] == '=' && boolean == 0)
		{
			printf("\"");
			boolean++;
		}
		i++;
	}
	printf("\"\n");
}
