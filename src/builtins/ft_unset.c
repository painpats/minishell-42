#include "../../inc/minishell.h"

static void	ft_new_envi(t_envir *envs, char *name)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = ft_calloc(ft_strlen_tab(envs->envi), sizeof(char *));
	i = 0;
	j = 0;
	while (envs->envi[i])
	{
		if (ft_strncmp(envs->envi[i], name, ft_strlen(name)) == 0)
			i++;
		else
		{
			new_env[j] = ft_strdup(envs->envi[i]);
			j++;
			i++;
		}
	}
	ft_free_tab(envs->envi);
	envs->envi = new_env;
}

void	ft_unset(t_tabcmd *tabcmd, t_envir *envs)
{
	char	**split;
	int		i;

	i = 1;
	split = ft_split_ws_quote(tabcmd->cmd);
	while (split[i])
	{
		if (check_if_already_in_env(envs, split[i]) == 1)
			ft_new_envi(envs, split[i]);
		i++;
	}
	ft_free_tab(split);
	g_exit = 0;
}
