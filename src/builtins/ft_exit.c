/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:43 by akloster          #+#    #+#             */
/*   Updated: 2024/09/27 00:06:08 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *exec)
{
	free_data(exec->data);
	if (exec->n_pipes > 0)
	{
		free_int_arr(&(exec->pipes), exec->n_pipes);
		free(*exec->pid);
		exec->pid = NULL;
	}
	free_ptr_arr(exec->env);
	free(exec->env);
	free(exec);
}

void	ft_exit(t_exec *exec)
{
	dup2(exec->std_out, STDOUT_FILENO);
	free_exec(exec);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
