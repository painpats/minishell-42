/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:32:42 by cbourre           #+#    #+#             */
/*   Updated: 2022/04/07 21:08:54 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nb_neg_putm(int nb_neg, int fd)
{
	if (nb_neg == 0)
		write(fd, "-", 1);
}

static void	ft_annexe(int nb, int fd)
{
	int		i;
	int		nb_neg;
	char	nb_char[12];

	i = 0;
	nb_neg = 1;
	if (nb < 0)
	{
		nb_neg = 0;
		nb = -nb;
	}
	else if (nb == 0)
		write(fd, "0", 1);
	while (nb > 0)
	{
		nb_char[i] = ((nb % 10) + '0');
		nb = nb / 10;
		i++;
	}
	ft_nb_neg_putm(nb_neg, fd);
	while (--i >= 0)
		write(fd, &nb_char[i], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n > -2147483648)
	{
		ft_annexe(n, fd);
	}
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
}
