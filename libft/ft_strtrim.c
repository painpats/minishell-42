/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:23:55 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/11 16:11:07 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == 0)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	while (ft_strrchr(set, s1[j]) != NULL)
		j--;
	str = ft_substr(s1, i, (j - i) + 1);
	return (str);
}
