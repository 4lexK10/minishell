/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 06:47:30 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:53:27 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	printf_llhex(unsigned long long args, char *base, int *count)
{
	if (args > 15)
	{
		printf_llhex(args / 16, base, count);
		if (*count == -1)
			return ;
		printf_llhex(args % 16, base, count);
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

void	printf_ptr(unsigned long long args, char *base, int *count)
{
	if (write(2, "0", 1) == -1 || write(2, "x", 1) == -1)
	{
		*count = -1;
		return ;
	}
	*count += 2;
	printf_llhex((unsigned long long) args, base, count);
}
