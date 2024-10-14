/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:37:55 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/18 17:46:05 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction cmpt str
static size_t	cmpt_str(char const *s, char c)
{
	size_t	i;
	size_t	cmpt;

	i = 0;
	cmpt = 0;
	if (s[0] == c || s[0] == '\0')
		cmpt = 0;
	else
		cmpt = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cmpt++;
		i++;
	}
	return (cmpt);
}

// fonction remplir tab
static char	**fill_tab(char const *s, char c, char **tab_str)
{
	size_t	i;
	size_t	m;
	size_t	len;

	i = 0;
	m = 0;
	len = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i + len] != c && s[i + len])
			len++;
		if (len > 0)
		{
			tab_str[m] = ft_substr(s, i, len);
			m++;
			i += len;
			len = 0;
		}
		while (s[i] == c && s[i])
			i++;
	}
	tab_str[m] = NULL;
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;
	size_t	len_tab;

	if (!s)
		return (NULL);
	len_tab = cmpt_str(s, c);
	tab_str = malloc(sizeof(char *) * (len_tab + 1));
	if (!tab_str)
		return (NULL);
	tab_str = fill_tab(s, c, tab_str);
	return (tab_str);
}
