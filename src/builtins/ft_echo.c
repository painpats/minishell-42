#include "../../inc/minishell.h"

static int	checkif_n(char *arg)
{
	int	i;

	i = 1;
	while (arg && arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		else
			i++;
	}
	return (1);
}

static void	ft_print_arg(char **arg, int i, int optn)
{
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (!optn)
		printf("\n");
}

void	ft_echo_2(char **cmd_echo)
{
	int	i;

	i = 0;
	while (cmd_echo[i])
	{
		cmd_echo[i] = ft_replace_quote(cmd_echo[i]);
		i++;
	}
}

void	ft_echo(char *arg)
{
	int		i;
	int		optn;
	char	**cmd_echo;

	i = 1;
	optn = 0;
	cmd_echo = ft_split_ws_quote(arg);
	if (cmd_echo[1] == NULL)
		write(1, "\n", 1);
	else
	{
		ft_echo_2(cmd_echo);
		while (cmd_echo[i])
		{
			if (cmd_echo[i][0] && cmd_echo[i][0] == '-'
				&& checkif_n(cmd_echo[i]))
				optn = 1;
			else
				break ;
			i++;
		}
		ft_print_arg(cmd_echo, i, optn);
	}
	ft_free_tab(cmd_echo);
	g_exit = 0;
}
