/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:30:13 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 18:21:38 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extrma_fork(t_exec *exec, int last) // factorise into two function calls ?
{
	int	in_check;
	int	out_check;

	if (last)
	{
		in_check = needs_preRedir(exec, exec->n_pipes);
		out_check = needs_postRedir(exec, exec->n_pipes);
		if (in_check == FOUND)
			return (FOUND);
		if (in_check == FAILED || out_check == FAILED)
			return (FAILED);
		if (dup2((exec->pipes)[exec->n_pipes - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NULL, OG_MSG));
		return (EXIT_SUCCESS);
	}
	in_check = needs_preRedir(exec, 0);
	out_check = needs_postRedir(exec, 0);
	if (in_check == FAILED || out_check == FAILED)
		return (FAILED);
	if (out_check == FOUND)
		return (FOUND);
	if (dup2((exec->pipes)[0][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}

static int	body_fork(int i, t_exec *exec)
{
	int	in_check;
	int	out_check;

	in_check = needs_preRedir(exec, i);
	out_check = needs_postRedir(exec, i);
	if (in_check == FAILED || out_check == FAILED)
		return (FAILED);
	if (in_check == FOUND || out_check == FOUND)
		return (EXIT_SUCCESS);
	if (in_check == FOUND)
	{
		if (dup2((exec->pipes)[i][1], STDOUT_FILENO) == -1)
			return (ft_error("dup2", NULL, OG_MSG));
		return (EXIT_SUCCESS);
	}
	if (out_check == FOUND)
	{
		if (dup2((exec->pipes)[i - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NULL, OG_MSG));
		return (EXIT_SUCCESS);
	}
	if (dup2((exec->pipes)[i][1], STDOUT_FILENO) == -1
		|| dup2((exec->pipes)[i - 1][0], STDIN_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (EXIT_SUCCESS);
}

void pipe_handler(t_exec *exec, int i)
{
	if (i == 0)
	{
		if (extrma_fork(exec, FIRST))
			exit(1);
	}
	else if (i == exec->n_pipes)
	{
		if (extrma_fork(exec, LAST))
			exit(1);
	}	
	else
	{
		if (body_fork(i, exec))
			exit(1);
	}
	pipe_cleaner(exec->pipes, exec->n_pipes);
}
