/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:43 by akloster          #+#    #+#             */
/*   Updated: 2024/09/28 22:18:44 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_exec(t_exec *exec)
{
	if (!exec)
		return (1);
	free_data(exec->data);
	if (exec->n_pipes > 0)
	{
		free_pipes(exec, exec->n_pipes);
		free(exec->pid);
		exec->pid = NULL;
	}
	free_env(exec);
	return (0);
}

void	ft_exit(t_exec *exec)
{
	dup2(exec->std_out, STDOUT_FILENO);
	free_exec(exec);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
