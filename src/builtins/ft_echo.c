/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:35 by akloster          #+#    #+#             */
/*   Updated: 2024/10/24 14:32:53 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for redir if redir and no pipe print nothing

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
