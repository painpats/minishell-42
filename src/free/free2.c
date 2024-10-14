#include "minishell.h"

void	ft_free_child(char *str, char **str2, t_envir *envs, t_tabcmd *tabcmd)
{
	free(str);
	ft_free_tab(str2);
	ft_free_tab(envs->envi);
	free(envs);
	ft_free_tabcmd(tabcmd);
}

void	ft_free_parent(t_tabcmd *tab, char **str, char *str2)
{
	ft_free_tab(str);
	free(str2);
	ft_free_tabcmd(tab);
}
