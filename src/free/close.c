#include "minishell.h"

void	ft_close_pipe(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	ft_close_fd(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (fd4 != -1)
		close(fd4);
}

int	is_the_last(t_tabfile *tabfile, int i, int type, int nb_file)
{
	int	j;
	int	k;

	j = i;
	k = 0;
	while (j < nb_file)
	{
		if (type == 1 && (tabfile[j].type == OUTFILE
				|| tabfile[j].type == APPEND))
					k++;
		if (type == 2 && (tabfile[j].type == INFILE
				|| tabfile[j].type == HEREDOC))
					k++;
		j++;
	}
	if (k == 1)
		return (1);
	return (0);
}

void	ft_close_all_file(t_tabfile *tabfile, int nb_file)
{
	int	i;

	i = 0;
	if (nb_file == 1)
		return ;
	while (i < nb_file)
	{
		if ((tabfile[i].type == OUTFILE || tabfile[i].type == APPEND)
			&& is_the_last(tabfile, i, 1, nb_file) == 0)
		{
			if (tabfile[i].fd >= 0)
				close(tabfile[i].fd);
		}
		if ((tabfile[i].type == INFILE || tabfile[i].type == HEREDOC)
			&& is_the_last(tabfile, i, 2, nb_file) == 0)
		{
			if (tabfile[i].fd >= 0)
				close(tabfile[i].fd);
		}
		i++;
	}
}
