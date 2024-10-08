/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 06:32:02 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:55:52 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(char c, int *count)
{
	if (write(2, &c, 1) == -1)
	{
		*count = -1;
		return (-1);
	}
	++(*count);
	return (0);
}

void	printf_nbr(int args, char *base, int *count)
{
	if (args == -2147483648)
	{
		if (ft_putchar('-', count) == -1 || ft_putchar('2', count) == -1)
			return ;
		printf_nbr(147483648, base, count);
	}
	else if (args < 0)
	{
		if (ft_putchar('-', count) == -1)
			return ;
		printf_nbr(-args, base, count);
	}
	else if (args > 9)
	{
		printf_nbr(args / 10, base, count);
		if (*count == -1)
			return ;
		printf_nbr(args % 10, base, count);
	}
	else
	{
		if (ft_putchar(base[args], count) == -1)
			return ;
	}
}
