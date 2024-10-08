/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 06:32:12 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:28:37 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_hex(unsigned int args, char *base, int *count)
{
	if (args > 15)
	{
		printf_hex(args / 16, base, count);
		if (*count == -1)
			return ;
		printf_hex(args % 16, base, count);
	}
	else
	{
		++(*count);
		if (write(2, &base[args], 1) == -1)
		{
			*count = -1;
			return ;
		}
	}
}
