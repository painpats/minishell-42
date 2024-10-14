#include "minishell.h"

static int	skip_to_char(char *str, char quote)
{
	int	i;
	int	boolean;

	i = 0;
	boolean = 0;
	while (str[i])
	{
		if (str[i] == quote)
			boolean++;
		if (boolean == 2)
			break ;
		i++;
	}
	return (i + 1);
}

static int	word_number(char *s)
{
	int	i;
	int	wordnb;

	i = 0;
	wordnb = 0;
	while (s[i] != '\0')
	{
		while (is_white_space(s[i]) == 1)
			i++;
		if (s[i] && is_white_space(s[i]) != 1)
			wordnb++;
		if ((s[i] == '\'' || s[i] == '\"') && isbetweenquote(s, i) == 0)
			i = skip_to_char(s, s[i]);
		while (is_white_space(s[i]) != 1 && s[i] != '\0')
			i++;
	}
	return (wordnb);
}

static char	**fill_tab(char *s, char **tabstr)
{
	int		i;
	int		j;
	int		wordlen;

	i = 0;
	j = 0;
	while (s[i])
	{
		wordlen = 0;
		while (s[i] && (is_white_space(s[i]) != 1 || isbetweenquote(s, i) == 0))
		{
			wordlen++;
			i++;
		}
		if (wordlen > 0)
		{
			tabstr[j] = ft_substr(s, i - wordlen, wordlen);
			if (!tabstr)
				return (NULL);
			j++;
		}
		if (s[i])
			i++;
	}
	return (tabstr);
}

char	**ft_split_ws_quote(char *s)
{
	char	**tabstr;
	size_t	wordnb;

	if (!s)
		return (NULL);
	wordnb = word_number(s);
	tabstr = ft_calloc(wordnb + 1, sizeof(char *));
	if (!tabstr)
		return (NULL);
	tabstr = fill_tab(s, tabstr);
	return (tabstr);
}
