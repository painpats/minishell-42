#include "minishell.h"

int	lexer_2(char **seq, t_tabcmd *tabcmd, char *str, int i)
{
	if (chevron(seq[i]) == 1)
	{
		if (files(seq[i], tabcmd, i, str) == 1)
		{
			ft_free_parent(tabcmd, seq, str);
			return (1);
		}
	}
	return (0);
}
