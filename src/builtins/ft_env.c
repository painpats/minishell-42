#include "../../inc/minishell.h"

void	ft_envs(t_envir *envs)
{
	int	i;

	i = 0;
	while (envs->envi[i])
	{
		if (ft_strchr(envs->envi[i], '=') != NULL)
			printf("%s\n", envs->envi[i]);
		i++;
	}
	g_exit = 0;
}
