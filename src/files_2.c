#include "minishell.h"

char	*recover_name(char *str, int i)
{
	char	*name;
	int		j;
	int		k;

	j = 0;
	k = i;
	while (str[k] && is_white_space(str[k]) == 0)
	{
		if (str[k] != '\'' && str[k] != '\"')
			j++;
		k++;
	}
	name = ft_calloc(j + 1, sizeof(char));
	j = 0;
	while (str[i] && is_white_space(str[i]) == 0)
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			name[j] = str[i];
			j++;
		}
		i++;
	}
	return (name);
}

int	stock_files(char *str, int i, t_typefile tfile, t_tabfile *tabfile)
{
	while (str[i] && is_white_space(str[i]) == 1)
		i++;
	tabfile->filename = recover_name(str, i);
	if (!tabfile->filename)
		return (1);
	tabfile->type = tfile;
	return (0);
}

int	check(char *str, int i, char chevron, int event)
{
	if (event == 1)
	{
		if (str[i] == chevron && str[i + 1] == chevron)
			return (0);
	}
	else if (event == 2)
	{
		if (str[i] == chevron && str[i + 1] != chevron)
			return (0);
	}
	return (1);
}
