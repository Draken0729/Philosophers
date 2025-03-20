/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:18:54 by quentin           #+#    #+#             */
/*   Updated: 2025/03/12 09:27:05 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    while (*str)
        my_putchar(*str++);
}

void my_putnbr(int n)
{
    if (n < 0)
	{
        my_putchar('-');
        n = -n;
    }
    if (n > 9)
        my_putnbr(n / 10);
    my_putchar(n % 10 + '0');
}

void ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    while (*format)
	{
        if (*format == '%' && *(format + 1))
		{
            format++;
            if (*format == 'd')
                my_putnbr(va_arg(args, int));
            else if (*format == 's')
                my_putstr(va_arg(args, char *));
            else if (*format == 'c')
                my_putchar((char)va_arg(args, int));
            else
                my_putchar('%'), my_putchar(*format);
        }
		else
		{
            my_putchar(*format);
        }
        format++;
    }
    va_end(args);
}