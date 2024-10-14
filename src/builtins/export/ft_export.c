#include "minishell.h"

void	ft_print_export(t_envir *envs)
{
	char	**tab_env;
	int		i;
	int		j;

	tab_env = ft_strdup_tab(envs->envi);
	while (tab_env)
	{
		i = 0;
		j = 0;
		while (tab_env[i] != NULL)
		{
			if (tab_env[i] != NULL && tab_env[j] != NULL
				&& ft_strcmp(tab_env[i], tab_env[j]) <= 0)
				j = i;
			i++;
		}
		if (tab_env[j] != NULL && ft_strchr(tab_env[j], '=') == NULL)
			printf("declare -x %s\n", tab_env[j]);
		else if (tab_env[j] != NULL && ft_strchr(tab_env[j], '=') != NULL)
			ft_print_export_quote(tab_env[j]);
		tab_env = ft_realloc(tab_env, j);
		if (!tab_env)
			break ;
	}
}

void	ft_export_create_line(char *str, t_envir *envs, char *name, int start)
{
	char	*line;
	int		i;
	int		j;

	i = start;
	j = ft_strlen(name);
	j += ft_count(str, i);
	line = ft_calloc(j + 2, sizeof(char));
	j = 0;
	while (name[j])
	{
		line[j] = name[j];
		j++;
	}
	i = start;
	line[j] = '=';
	j++;
	while (str[i])
	{
		line[j] = str[i];
		i++;
		j++;
	}
	free(name);
	ft_export_add_env(envs, line);
}

int	ft_export_append_2(t_envir *envs, char *name)
{
	int	i;

	i = 0;
	while (envs->envi[i])
	{
		if (ft_strncmp(envs->envi[i], name, ft_strlen(name)) == 0)
			break ;
		i++;
	}
	return (i);
}

void	ft_export_append(char *name, char *str, int start, t_envir *envs)
{
	int		i;
	int		j;
	int		k;
	char	*line;

	i = start;
	while (str[i])
		i++;
	j = ft_export_append_2(envs, name);
	line = ft_calloc(i + ft_strlen(envs->envi[j]), sizeof(char));
	i = -1;
	while (envs->envi[j][++i])
		line[i] = envs->envi[j][i];
	k = start;
	while (str[k])
	{
		line[i] = str[k];
		i++;
		k++;
	}
	free(envs->envi[j]);
	envs->envi[j] = ft_strdup(line);
	free(line);
	free(name);
}

void	ft_export(char *cmd, t_envir *envs)
{
	int		i;
	int		boolean;
	char	**tab_args;

	tab_args = ft_split_quote(cmd, ' ');
	if (ft_strlen_tab(tab_args) == 1)
		ft_print_export(envs);
	i = 1;
	while (tab_args[i] != NULL)
	{	
		boolean = 0;
		tab_args[i] = ft_replace_quote(tab_args[i]);
		if (check_export(tab_args[i]) == 1)
			boolean = 1;
		else
		{
			if (ft_strchr(tab_args[i], '=') != NULL)
				ft_export_arg(tab_args[i], envs);
			else if (check_if_already_in_env(envs, tab_args[i]) == 0)
				ft_export_add_env(envs, ft_strdup(tab_args[i]));
		}
		i++;
	}
	ft_free_tab(tab_args);
	g_exit = boolean;
}
