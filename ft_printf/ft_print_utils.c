/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:58 by qbaret            #+#    #+#             */
/*   Updated: 2024/11/15 15:43:49 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar('-');
		i++;
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
	i++;
	return (i);
}

int	ft_putchar(char c)
{
	int	i;

	i = 0;
	write(1, &c, 1);
	i++;
	return (i);
}

unsigned int	ft_printhex_min(unsigned int nombre)
{
	char	*hex_digits;
	int		index;
	char	buffer[9];

	hex_digits = "0123456789abcdef";
	index = 8;
	buffer[index--] = '\0';
	if (nombre == 0)
	{
		buffer[index] = '0';
		write(1, &buffer[index], 1);
		return (1);
	}
	while (nombre > 0 && index >= 0)
	{
		buffer[index--] = hex_digits[nombre % 16];
		nombre /= 16;
	}
	write(1, &buffer[index + 1], 7 - index);
	return (7 - index);
}

unsigned int	ft_printhex_maj(unsigned int nombre)
{
	char	*hex_digits;
	int		index;
	char	buffer[9];

	hex_digits = "0123456789ABCDEF";
	index = 8;
	buffer[index--] = '\0';
	if (nombre == 0)
	{
		buffer[index] = '0';
		write(1, &buffer[index], 1);
		return (1);
	}
	while (nombre > 0 && index >= 0)
	{
		buffer[index--] = hex_digits[nombre % 16];
		nombre /= 16;
	}
	write(1, &buffer[index + 1], 7 - index);
	return (7 - index);
}
