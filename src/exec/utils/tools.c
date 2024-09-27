/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:50:03 by akloster          #+#    #+#             */
/*   Updated: 2024/09/27 03:26:25 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pre_exec_free(t_exec *exec)
{
	if (exec->n_pipes > 0)
	{
		free_int_arr(&(exec->pipes), exec->n_pipes);
		free(*exec->pid);
		*(exec->pid) = NULL;
	}
}

int	add_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (write(STDOUT_FILENO, "=\"", 2) == -1)
				return (1);
		}
		else
			if (write(STDOUT_FILENO, &str[i], 1) == -1)
				return (1);
	}
	if (write(STDOUT_FILENO, "\"\n", 2) == -1)
		return (1);
	return (0);
}
