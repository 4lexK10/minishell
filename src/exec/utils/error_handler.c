/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:24:08 by akloster          #+#    #+#             */
/*   Updated: 2024/10/10 12:34:21 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str, char *name, int need)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	if (need == MY_MSG)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		if (name)
			ft_putstr_fd(name, STDERR_FILENO);
		return (1);
	}
	if (name)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		perror(name);
	}
	else
		perror(str);
	return (1);
}
