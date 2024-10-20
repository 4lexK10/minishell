/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:35 by akloster          #+#    #+#             */
/*   Updated: 2024/10/19 17:05:31 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for redir if redir and no pipe print nothing

int	ft_echo(t_exec *exec, t_data *data)
{
	bool	n_flag;

	n_flag = false;
	if ()
	if (data && !ft_strncmp(data->word, "-n", 3))
	{
		n_flag = true;
		data = data->next;
	}
	while (data && data->token == STRING)
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
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}
