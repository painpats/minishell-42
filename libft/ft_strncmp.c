/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:14:29 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/11 11:13:14 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	while (i < n && (src1[i] != '\0' || src2[i] != '\0'))
	{
		if (src1[i] < src2[i] || src1[i] > src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}
