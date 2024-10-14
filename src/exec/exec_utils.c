#include "minishell.h"

int	is_builtins(char *cmd)
{
	if (ft_strncmp_without_ws("echo", cmd, 4) == 0)
		return (1);
	else if (ft_strncmp_without_ws("cd", cmd, 2) == 0)
		return (1);
	else if (ft_strncmp_without_ws("pwd", cmd, 3) == 0)
		return (1);
	else if (ft_strncmp_without_ws("export", cmd, 6) == 0)
		return (1);
	else if (ft_strncmp_without_ws("unset", cmd, 5) == 0)
		return (1);
	else if (ft_strncmp_without_ws("env", cmd, 3) == 0)
		return (1);
	else if (ft_strncmp_without_ws("exit", cmd, 4) == 0)
		return (1);
	return (0);
}

void	ft_builtins(t_tabcmd *tabcmd, t_envir *envs)
{
	if (ft_strncmp_without_ws("echo", tabcmd->cmd, 4) == 0)
		ft_echo(tabcmd->cmd);
	else if (ft_strncmp_without_ws("cd", tabcmd->cmd, 2) == 0)
		ft_cd(tabcmd, envs);
	else if (ft_strncmp_without_ws("pwd", tabcmd->cmd, 3) == 0)
		ft_pwd();
	else if (ft_strncmp_without_ws("export", tabcmd->cmd, 6) == 0)
		ft_export(tabcmd->cmd, envs);
	else if (ft_strncmp_without_ws("unset", tabcmd->cmd, 5) == 0)
		ft_unset(tabcmd, envs);
	else if (ft_strncmp_without_ws("env", tabcmd->cmd, 3) == 0)
		ft_envs(envs);
}
