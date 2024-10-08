/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 06:32:21 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:12:08 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	printf_str(char *args, int *count)
{
	int	i;

	i = 0;
	if (!args)
	{
		if (write(2, "(null)", 6) == -1)
		{
			*count = -1;
			return ;
		}
		*count += 6;
		return ;
	}
	while (args[i] != '\0')
	{
		if (write(2, &args[i++], 1) == -1)
		{
			*count = -1;
			return ;
		}
	}
	*count += i;
}
