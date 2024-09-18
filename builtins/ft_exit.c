/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:43 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 02:12:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_exec *exec, char ***env)
{
	free_data(exec->data);
	free_ptr_arr(env);
	if (exec->n_pipes > 0)
	{
		free_int_arr(&(exec->pipes), exec->n_pipes);
		free(*exec->pid);
		exec->pid = NULL;
	}
	free(exec);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}
