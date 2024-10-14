#include "minishell.h"

static char	**ft_env(char **env)
{
	int		i;
	int		len;
	char	*line;
	char	**tab;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	len = ft_strlen(env[i]) - 5;
	line = ft_substr(env[i], 5, len);
	if (!line)
		return (NULL);
	tab = ft_split(line, ':');
	free(line);
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_stock_cmd(char *cmd)
{
	char	**tab;

	tab = ft_split_quote(cmd, ' ');
	if (!tab)
		return (NULL);
	return (tab);
}

static char	*path_finding(char **tabpath, char *cmd)
{
	char	*cmd_path;
	char	*command;
	int		i;

	if (access(cmd, X_OK | F_OK) == 0)
		return (ft_strdup(cmd));
	command = ft_strdup(cmd);
	if (cmd[0] != '/')
	{
		free(command);
		command = ft_strjoin("/", cmd);
	}
	i = -1;
	while (tabpath[++i])
	{
		cmd_path = ft_strjoin(tabpath[i], command);
		if (access(cmd_path, X_OK | F_OK) == 0)
		{
			free(command);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(command);
	return (NULL);
}

char	*ft_access(char *cmd)
{
	char	**tab_cmd;
	char	*tmp;

	tab_cmd = ft_stock_cmd(cmd);
	if (access(tab_cmd[0], X_OK | F_OK) == 0)
	{
		tmp = ft_strdup(tab_cmd[0]);
		ft_free_tab(tab_cmd);
		return (tmp);
	}
	else
	{
		ft_free_tab(tab_cmd);
		return (NULL);
	}
}

char	*ft_path(char *cmd, char **env)
{
	char	**tabpath;
	char	**cmd_split;
	char	*cmdpath;

	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_strdup("error"));
	tabpath = ft_env(env);
	if (!tabpath)
		return (ft_access(cmd));
	cmd_split = ft_stock_cmd(cmd);
	if (cmd_split[0] == NULL)
	{
		ft_free_tab(cmd_split);
		ft_free_tab(tabpath);
		return (ft_strdup("error"));
	}
	cmdpath = path_finding(tabpath, cmd_split[0]);
	ft_free_tab(tabpath);
	ft_free_tab(cmd_split);
	if (!cmdpath)
		return (NULL);
	return (cmdpath);
}
