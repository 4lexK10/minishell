/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/09/27 01:49:23 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	*init_pids(int n_pipes)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (pid_t *)malloc((n_pipes + 1) * sizeof(pid_t));
	if (!pids)
		return (NULL);
	while (++i <= n_pipes)
		pids[i] = 0;
	return (pids);
}

static int	no_pipe_exec(t_exec *exec)
{
	int		pid;
	t_data	*ret;

	pid = 0;
	ret = find_built(*(exec->data));
	if (!ret)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
	}
	if (pid == 0)
	{
		if (needs_preRedir(exec, 0) == 1)
			exit(1);
		if (needs_postRedir(exec, 0) == 1)
			exit(1);
		return (executioner(exec, 0));
	}
	if (pid && waitpid(pid, NULL, 0) == -1)
		return (ft_error("waitpid", NO_EXIT));
	return (0);
}

static int	parent_close_wait(t_exec *exec)
{
	int	i;

	i = -1;
	if (pipe_cleaner(exec->pipes, exec->n_pipes))
		return (1);
	while (++i <= exec->n_pipes)
		waitpid((*(exec->pid))[i], NULL, 0);
	free_int_arr(&(exec->pipes), exec->n_pipes);
	free(*(exec->pid));
	free_data(exec->data);
	free(exec);
	return (0);
}
static void	exec_child(t_exec *exec, int i)
{
	pipe_handler(exec, i);
	executioner(exec, i);
	free_exec(exec);
	if (exec->build_exec)
	{
		free(exec->user_input);
		exit(0);
	}
	exit(1);
}

int process_handler(t_exec *exec)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = NULL;
	if (exec->n_pipes == 0)
		return (no_pipe_exec(exec));
	pids = init_pids(exec->n_pipes);
	if (!pids)
		return (1);
	exec->pid = &pids;
	while (++i <= exec->n_pipes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
			exec_child(exec, i);
	}
	return (parent_close_wait(exec));
}
