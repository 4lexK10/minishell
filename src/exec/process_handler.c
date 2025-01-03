/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:02 by akloster         ###   ########.fr       */
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
	int		status;

	status = 0;
	if (!find_built(*exec->data))
	{
		if (cmd_exec(exec))
			return (free_data(exec->data), 1);
	}
	else
	{
		if (built_exec(exec))
			return (free_data(exec->data), 1);
	}
	free_data(exec->data);
	return (0);
}

static int	parent_close_wait(t_exec *exec)
{
	int	i;
	int	status;

	i = -1;
	if (pipe_cleaner(exec->pipes, exec->n_pipes))
		return (1);
	while (++i <= exec->n_pipes)
	{
		waitpid((exec->pid)[i], &status, 0);
		if (i == exec->n_pipes)
		{
			g_last_val = WEXITSTATUS(status);
			if (g_last_val == 255)
				g_last_val += 3;
			if (status == 2)
				g_last_val = 130;
		}
	}
	free_pipes(exec, exec->n_pipes);
	free(exec->pid);
	exec->pid = NULL;
	free_data(exec->data);
	return (0);
}

static void	exec_child(t_exec *exec, int i)
{
	pipe_handler(exec, i);
	is_cmd_valid(exec, i);
	if (!executioner(exec, i))
	{
		free_data(exec->data);
		free(exec->pid);
		exec->pid = NULL;
		free_pipes(exec, exec->n_pipes);
		exit(0);
	}
	free_exec(exec);
	exit(1);
}

int	process_handler(t_exec *exec)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = NULL;
	if (here_doc_handler(exec))
		return (1);
	if (exec->n_pipes == 0)
		return (no_pipe_exec(exec));
	pids = init_pids(exec->n_pipes);
	if (!pids)
		return (1);
	exec->pid = pids;
	while (++i <= exec->n_pipes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_error("fork", NULL, OG_MSG));
		if (pids[i] == 0)
			exec_child(exec, i);
	}
	return (parent_close_wait(exec));
}
