#include "minishell.h"

static int	ft_strlen_quote(char *str, int start, char quote)
{
	int	i;

	i = start;
	if (str[i] == quote)
		i++;
	while (str[i] != quote)
		i++;
	return (i);
}

static char	*take_limiter(char *str, int start)
{
	int		i;
	int		j;
	char	*new;

	i = start;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		i++;
		j++;
	}
	new = ft_calloc(j + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = start;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

static char	*remove_limiter_quote(char *str, char quote, int fq)
{
	int		i;
	int		j;
	char	*new;

	i = fq + 1;
	j = 0;
	new = ft_calloc(ft_strlen_quote(str, fq, quote) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i] != quote)
	{
		new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

static char	*check_limiter(char *str, int i)
{
	char	*limiter;

	if (str[i] == ' ')
		i++;
	if (str[i] == '"' && str[i + 1] == '"')
		return ("\n");
	if (isbetweenquote(str, i + 1) == 0)
		limiter = remove_limiter_quote(str, str[i], i);
	else
		limiter = take_limiter(str, i);
	if (!limiter)
		return (NULL);
	limiter = ft_strjoin_free(limiter, "\n");
	if (!limiter)
		return (NULL);
	return (limiter);
}

char	*recover_limiter(char *str, int i)
{
	char	*limiter;

	while (str[i] && str[i] == '<')
		i++;
	limiter = check_limiter(str, i);
	if (!limiter)
		return (NULL);
	return (limiter);
}
