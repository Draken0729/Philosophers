/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:42:34 by qbaret            #+#    #+#             */
/*   Updated: 2024/11/15 15:26:43 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex(unsigned long nombre)
{
	char	*hex_digits;
	char	buffer[17];
	int		index;

	hex_digits = "0123456789abcdef";
	index = 16;
	buffer[index--] = '\0';
	if (nombre == 0)
	{
		buffer[index] = '0';
	}
	else
	{
		while (nombre > 0 && index >= 0)
		{
			buffer[index--] = hex_digits[nombre % 16];
			nombre /= 16;
		}
	}
	write(1, &buffer[index + 1], 15 - index);
	return (15 - index);
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;

	if (!ptr)
		return (ft_putstr("(nil)"));
	address = (unsigned long)ptr;
	return (ft_putstr("0x") + print_hex(address));
}

/*int	main(void)
{
	int	x;

	x = 42;
	ft_print_pointer(&x);
	write(1, "\n", 1);
	return (0);
}*/
