#include "minishell.h"

int	isbetweenquote(char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			j++;
			while (str[j] != quote)
				j++;
			if (j > i)
				return (0);
		}
		j++;
	}
	return (1);
}

int	chevron(char *str)
{
	int	outfile;
	int	infile;
	int	i;

	i = 0;
	infile = 0;
	outfile = 0;
	while (str[i])
	{
		if (str[i] == '>')
			outfile++;
		if (str[i] == '<')
			infile++;
		i++;
	}
	if (infile != 0 || outfile != 0)
		return (1);
	return (0);
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_strncmp_without_ws(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*temps1;
	unsigned char	*temps2;

	i = 0;
	j = 0;
	temps1 = (unsigned char *)s1;
	temps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (is_white_space(temps2[i]) == 1)
		i++;
	while (j < n && (temps1[j] != '\0' || temps2[i] != '\0'))
	{
		if (temps1[j] != temps2[i])
			return (temps1[j] - temps2[i]);
		i++;
		j++;
	}
	if (temps2[i] != '\0' && is_white_space(temps2[i]) == 0)
		return (1);
	return (0);
}
