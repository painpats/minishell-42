#include "../../inc/minishell.h"

static int	ft_check_overflow(char *str)
{
	int	len;

	if (str[0] == '-')
	{
		len = ft_strlen(str);
		if (len > 20 || ft_strcmp("-9223372036854775808", str) < 0)
			return (1);
	}
	else if (str[0] == '+')
	{
		len = ft_strlen(str);
		if (len > 20 || ft_strcmp("+9223372036854775807", str) < 0)
			return (1);
	}
	else
	{
		len = ft_strlen(str);
		if (len > 19 || ft_strcmp("9223372036854775807", str) < 0)
			return (1);
	}
	return (0);
}

char	*ft_atoll_check_exit(char *nptr)
{
	int				i;
	long long int	neg;
	long long int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	if (ft_check_overflow(nptr) == 1)
		return ("error");
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return ("ok");
}

static void	ft_exit_2(t_tabcmd *tab, t_pipe *pipes, t_envir *envs, char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (ft_isdigit(str[1][i]) == 0 && str[1][0] != '-')
		{	
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: numeric argument required\n", 2);
			ft_free_exit(tab, envs, str, pipes);
			g_exit = 2;
			exit (g_exit);
		}
		i++;
	}
	if (ft_strlen_tab(str) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exit = 1;
		return ;
	}
}

void	ft_exit(t_tabcmd *tabcmd, t_pipe *pipes, t_envir *envs, int j)
{
	char	**cmd_split;

	cmd_split = ft_split_quote(tabcmd[j].cmd, ' ');
	if (ft_strlen_tab(cmd_split) == 1)
	{
		ft_free_exit(tabcmd, envs, cmd_split, pipes);
		printf("exit\n");
		exit(g_exit);
	}
	if (ft_strncmp(ft_atoll_check_exit(cmd_split[1]), "error", 5) == 0)
	{
		ft_free_tab(cmd_split);
		free(tabcmd[j].cmd);
		tabcmd[j].cmd = ft_strdup("exit *");
		ft_exit(tabcmd, pipes, envs, j);
	}
	ft_exit_2(tabcmd, pipes, envs, cmd_split);
	if (ft_strlen_tab(cmd_split) > 2)
	{
		ft_free_tab(cmd_split);
		return ;
	}
	g_exit = (unsigned char)ft_atoll(cmd_split[1]);
	ft_free_exit(tabcmd, envs, cmd_split, pipes);
	exit(g_exit);
}
