#include "minishell.h"

static void	ft_fill_new_str(char *str, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && isbetweenquote(str, i) == 1)
			i++;
		else
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
}

char	*ft_replace_quote(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && isbetweenquote(str, i) == 1)
			i++;
		else
		{
			j++;
			i++;
		}
	}
	new_str = ft_calloc(j + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_fill_new_str(str, new_str);
	free(str);
	return (new_str);
}
