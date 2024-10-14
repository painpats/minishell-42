#include "minishell.h"

static int	ft_count_j(t_tabcmd *tabcmd, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < tabcmd[k].nb_file)
	{
		if (tabcmd[k].file[j].fd != -1)
			j++;
		i++;
	}
	return (j);
}

static int	files_3(t_tabcmd *tabcmd, t_init_files *s_f)
{
	if (check(s_f->str, s_f->i, '>', 2) == 0
		&& isbetweenquote(s_f->str, s_f->i) == 1)
	{
		if (stock_files(s_f->str, s_f->i + 1, OUTFILE,
				&tabcmd[s_f->k].file[s_f->j]) == 1)
			return (1);
		s_f->j++;
	}
	else if (check(s_f->str, s_f->i, '<', 2) == 0
		&& isbetweenquote(s_f->str, s_f->i) == 1)
	{
		if (stock_files(s_f->str, s_f->i + 1, INFILE,
				&tabcmd[s_f->k].file[s_f->j]) == 1)
			return (1);
		s_f->j++;
	}
	return (0);
}

static int	files_2(t_tabcmd *tabcmd, t_init_files *s_f)
{
	if (check(s_f->str, s_f->i, '>', 1) == 0
		&& isbetweenquote(s_f->str, s_f->i) == 1)
	{
		if (stock_files(s_f->str, s_f->i + 2, APPEND,
				&tabcmd[s_f->k].file[s_f->j]) == 1)
			return (1);
		s_f->i++;
		s_f->j++;
	}
	else if (check(s_f->str, s_f->i, '<', 1) == 0
		&& isbetweenquote(s_f->str, s_f->i) == 1)
	{
		s_f->j++;
		s_f->i++;
	}
	else if (files_3(tabcmd, s_f) == 1)
		return (1);
	return (0);
}

static t_init_files	*init_struct_file(char *st, int l, char *in, t_tabcmd *tab)
{
	t_init_files	*struct_files;

	struct_files = malloc(sizeof(t_init_files));
	struct_files->i = 0;
	struct_files->j = ft_count_j(tab, l);
	struct_files->k = l;
	struct_files->str = ft_strdup(st);
	struct_files->input_str = ft_strdup(in);
	return (struct_files);
}

int	files(char	*str, t_tabcmd *tabcmd, int k, char *input_str)
{
	t_init_files	*s_files;

	s_files = init_struct_file(str, k, input_str, tabcmd);
	while (str[s_files->i])
	{
		if (chevron(str) != 0)
		{
			if (files_2(tabcmd, s_files) == 1)
				return (1);
		}
		s_files->i++;
	}
	free(s_files->str);
	free(s_files->input_str);
	free(s_files);
	return (0);
}
