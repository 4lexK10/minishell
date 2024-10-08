/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:43:10 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:39:51 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	printf_handler(va_list args, char c, int *count)
{
	char	d;

	if (c == 'c')
	{
		d = va_arg(args, int);
		if (write(2, &d, 1) == -1)
			return (-1);
		++(*count);
	}
	else if (c == 's')
		printf_str(va_arg(args, char *), count);
	else if (c == 'p')
		printf_ptr(va_arg(args, unsigned long long), "0123456789abcdef", count);
	else if (c == 'd' || c == 'i')
		printf_nbr(va_arg(args, int), "0123456789", count);
	else if (c == 'u')
		printf_u_nbr(va_arg(args, unsigned int), "0123456789", count);
	else if (c == 'x')
		printf_hex(va_arg(args, int), "0123456789abcdef", count);
	else if (c == 'X')
		printf_hex(va_arg(args, int), "0123456789ABCDEF", count);
	if (*count == -1)
		return (-1);
	return (*count);
}

static int	checker(const char c, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		if (s[i++] == c)
			return (1);
	return (0);
}

static int	parser(const char *s, va_list args, int *count)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '%')
		{
			if (write(2, &s[i], 1) == -1)
				return (-1);
			++(*count);
		}
		if (s[i] == '%' && s[i + 1] == '%')
		{
			if (write(2, &s[i], 1) == -1)
				return (-1);
			i += 2;
			++(*count);
		}
		else if (s[i++] == '%' && checker(s[i], "cspdiuxX"))
		{
			if (printf_handler(args, s[i++], count) == -1)
				return (-1);
		}
	}
	return (*count);
}

int	ft_printf(const char *s, ...)
{
	int		size;
	int		*count;
	va_list	args;

	if (!s)
	{
		if (write(2, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	count = (int *)malloc(sizeof(int));
	if (!count)
		return (-1);
	*count = 0;
	va_start(args, s);
	size = parser(s, args, count);
	free(count);
	va_end(args);
	return (size);
}
