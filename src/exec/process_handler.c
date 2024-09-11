/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/09/11 02:20:22 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*init_pids(int n_pipes)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (int *)malloc((n_pipes + 1) * sizeof(int));
	if (!pids)
		return (NULL);
	while (++i <= n_pipes)
		pids[i] = 0;
	return (pids);
}

static int	no_pipe_exec(t_exec *exec)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (needs_preRedir(exec, 0) == 1)
			exit(1);
		if (needs_postRedir(exec, 0) == 1)
			exit(1);
		executioner(exec, 0);
		exit(1);
	}
	if (waitpid(pid, NULL, 0) == -1)
		return (ft_error("waitpid", NO_EXIT));
	return (0);
}

static int	parent_close_wait(int **pipes, int **pids, int n_pipes)
{
	int	i;

	i = -1;
	if (pipe_cleaner(pipes, n_pipes))
		return (1);
/* 	while (wait(NULL) > 0)
		; */
	while (++i <= n_pipes)
	{
		waitpid((*pids)[i], NULL, 0);
	}
	free(*pids);
	*pids = NULL;
	return (0);
}
static void	exec_child(t_exec *exec, int i)
{
	exec->in_pipe = true;
	pipe_handler(exec, i);
	executioner(exec, i);
	exit(1);
}

int process_handler(t_exec *exec)
{
	t_data	*temp;
	pid_t	*pids;
	int		i;
	int		res;

	i = -1;
	temp = *(exec->data);
	pids = init_pids(exec->n_pipes);
	exec->pid = &pids;
	if (!pids)
		return (1);
	if (exec->n_pipes == 0)
		return (no_pipe_exec(exec));
	while (++i <= exec->n_pipes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
			exec_child(exec, i);
	}
	if (parent_close_wait(exec->pipes, &pids, exec->n_pipes))
		return (1);
	return (0);
}

