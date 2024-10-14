#include "minishell.h"

// Ctrl + c = SIGINT (interrupt the process)
// Ctrl + d = SIGQUIT (quit the process)

void	ctrl_c(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit = 130;
}

void	ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 256;
		close(0);
		printf("\n");
	}
}

void	signal_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit = 131;
	}
}
