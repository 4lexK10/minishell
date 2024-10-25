/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:35 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 17:05:03 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_exec *exec, t_data *data)
{
	bool	n_flag;

	n_flag = false;
	if (data && !ft_strncmp(data->word, "-n", 3))
	{
		n_flag = true;
		data = data->next;
	}
	while (data && (data->token == STRING || data->token == ABS_PATH
			|| data->token == BUILT))
	{
		if (ft_putstr_fd(data->word, STDOUT_FILENO))
			return (ft_error("write", NULL, OG_MSG));
		if (data->next && data->next->token == STRING)
			if (ft_putstr_fd(" ", STDOUT_FILENO))
				return (ft_error("write", NULL, OG_MSG));
		data = data->next;
	}
	if (!n_flag)
		if (ft_putstr_fd("\n", STDOUT_FILENO))
			return (ft_error("write", NULL, OG_MSG));
	return (reset_std_io(exec));
}
