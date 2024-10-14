#include "minishell.h"

void	heredoc_ctrl_c(int fd)
{
	g_exit = 130;
	dup2(fd, 0);
	close(fd);
}

void	heredoc_ctrl_d(int fd)
{
	ft_putstr_fd("mimish: warning: here-document error\n", 2);
	g_exit = 0;
	close(fd);
}

void	ft_read_heredoc_2(char *str, int file)
{
	ft_putstr_fd(str, file);
	free(str);
	printf("\n");
}

int	ft_read_heredoc(char *limiter, int file)
{
	char	*str;
	int		fd;

	fd = dup(STDIN_FILENO);
	while (1)
	{
		str = get_next_line(0);
		signal(SIGQUIT, SIG_IGN);
		if (g_exit == 256)
		{
			heredoc_ctrl_c(fd);
			return (1);
		}
		if (!str)
		{
			heredoc_ctrl_d(fd);
			return (1);
		}
		if (!str || ft_strcmp(str, limiter) == 0)
			break ;
		ft_read_heredoc_2(str, file);
	}
	free (str);
	close(fd);
	return (0);
}
