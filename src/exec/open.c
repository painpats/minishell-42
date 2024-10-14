#include "minishell.h"

int	ft_open_infile(t_tabfile *tabfile, t_pipe *pipes)
{
	if (tabfile->type == INFILE || tabfile->type == HEREDOC)
	{
		pipes->read = open(tabfile->filename, O_RDONLY, 0644);
		tabfile->fd = pipes->read;
	}
	if (pipes->read == -1)
	{
		perror("infile");
		return (1);
	}
	return (0);
}

int	ft_open_outfile(t_tabfile *tabfile, t_pipe *pipes)
{
	if (tabfile->type == OUTFILE)
	{
		pipes->write = open(tabfile->filename, O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		tabfile->fd = pipes->write;
	}
	else if (tabfile->type == APPEND)
	{
		pipes->write = open(tabfile->filename, O_WRONLY
				| O_APPEND | O_CREAT, 0644);
		tabfile->fd = pipes->write;
	}
	if (pipes->write == -1)
	{
		perror("outfile");
		return (1);
	}
	return (0);
}

int	open_file(t_tabcmd tabcmd, t_pipe *pipes)
{
	int	i;

	i = 0;
	pipes->write = -1;
	while (i < tabcmd.nb_file)
	{
		if (tabcmd.file[i].type == INFILE || tabcmd.file[i].type == HEREDOC)
		{
			if (ft_open_infile(&tabcmd.file[i], pipes) == 1)
				return (1);
		}
		else if (tabcmd.file[i].type == OUTFILE
			|| tabcmd.file[i].type == APPEND)
		{
			if (ft_open_outfile(&tabcmd.file[i], pipes) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
