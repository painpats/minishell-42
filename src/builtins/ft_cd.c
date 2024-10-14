#include "../../inc/minishell.h"

void	ft_update_pwd(t_envir *envs)
{
	char	*old;
	char	*oldpwd;
	char	*pw;
	char	*pwd;

	old = ft_recover_variable("PWD", envs);
	oldpwd = ft_strjoin("export OLDPWD=", old);
	free(old);
	pw = getcwd(NULL, 0);
	pwd = ft_strjoin("export PWD=", pw);
	free(pw);
	ft_export(oldpwd, envs);
	ft_export(pwd, envs);
	free(pwd);
	free(oldpwd);
}

static char	*ft_malloc_path(t_tabcmd *tabcmd, int *k)
{
	char	*path;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (tabcmd->cmd[i] && is_white_space(tabcmd->cmd[i]) == 1)
		i++;
	while (tabcmd->cmd[i] && is_white_space(tabcmd->cmd[i]) == 0)
		i++;
	while (tabcmd->cmd[i] && is_white_space(tabcmd->cmd[i]) == 1)
		i++;
	while (tabcmd->cmd[i] && is_white_space(tabcmd->cmd[i]) == 0)
	{
		i++;
		j++;
	}
	path = ft_calloc(j + 1, sizeof(char));
	*k = i - j;
	return (path);
}

void	ft_cd(t_tabcmd *tabcmd, t_envir *envs)
{
	char	*path;
	int		i;
	int		j;
	int		boolean;

	i = 0;
	tabcmd->cmd = ft_replace_quote(tabcmd->cmd);
	path = ft_malloc_path(tabcmd, &i);
	j = 0;
	while (tabcmd->cmd[i] && is_white_space(tabcmd->cmd[i]) == 0)
	{
		path[j] = tabcmd->cmd[i];
		i++;
		j++;
	}
	if (chdir(path) == -1)
	{
		boolean = 1;
		perror("cd");
	}
	else
		boolean = 0;
	ft_update_pwd(envs);
	free(path);
	g_exit = boolean;
}
