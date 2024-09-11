/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:35 by akloster          #+#    #+#             */
/*   Updated: 2024/09/11 20:26:54 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data)
{
	bool	n_flag;

	n_flag = false;
	if (ft_strnstr(data->word, "-n", 2))
	{
		n_flag = true;
		data = data->next;
	}
	while (data->word)
	{
		if (ft_putstr_fd(data->next->word, STDOUT_FILENO))
			return (ft_error("write", NO_EXIT));
		data = data->next;
	}
	if (!n_flag)
		if (ft_putstr_fd("\n", STDOUT_FILENO))
			return (ft_error("write", NO_EXIT));
	return (0);
}
