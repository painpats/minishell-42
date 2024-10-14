/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:10:58 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/12 20:32:20 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	len_n(int n)
{
	unsigned int	len;
	long int		nbr;

	nbr = n;
	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static void	check_neg(char *str, long int *nbr)
{
	if (*nbr < 0)
	{
		str[0] = '-';
		*nbr *= -1;
	}
}

char	*ft_itoa(int n)
{
	int			len;
	long int	nbr;
	char		*str;

	nbr = n;
	len = len_n(n);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	check_neg(str, &nbr);
	len--;
	while (nbr > 0 && len >= 0)
	{
		str[len] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		len--;
	}
	return (str);
}
