/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 08:43:02 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/06 11:48:20 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			k = i;
			while (big[k] == little[j] && little[j] != '\0' && k < len)
			{
				k++;
				j++;
			}
			if (little[j] == '\0')
				return ((char *)big + i);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
