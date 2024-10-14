#include "minishell.h"

t_envir	*get_env(char **env)
{
	t_envir	*envs;

	envs = malloc(sizeof(t_envir));
	if (!envs)
	{
		ft_putstr_fd("Error with malloc of env\n", 2);
		exit(EXIT_FAILURE);
	}
	envs->envi = ft_strdup_tab(env);
	if (!envs->envi)
	{
		free(envs);
		ft_putstr_fd("Error with malloc of env\n", 2);
		exit(EXIT_FAILURE);
	}
	return (envs);
}
