/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:35 by akloster          #+#    #+#             */
/*   Updated: 2024/09/26 23:31:11 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_exec *exec, t_data *data)
{
	bool	n_flag;

	n_flag = false;
	if (!ft_strncmp(data->word, "-n", 3))
	{
		n_flag = true;
		data = data->next;
	}
	while (data && data->token == STRING)
	{
		if (ft_putstr_fd(data->word, STDOUT_FILENO))
			return (ft_error("write", NO_EXIT));
		data = data->next;
	}
	if (!n_flag)
		if (ft_putstr_fd("\n", STDOUT_FILENO))
			return (ft_error("write", NO_EXIT));
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (0);
}
