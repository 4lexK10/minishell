/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/10/14 18:41:06 by akloster         ###   ########.fr       */
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
	int		status;

	pid = 0;
	ret = find_built(*(exec->data));
	status = 0;
	if (!ret)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
	}
	if (pid == 0)
	{
		if (needs_preRedir(exec, 0) == 1 || needs_postRedir(exec, 0) == 1)
			exit(1);
		is_cmd_valid(exec, 0);
		executioner(exec, 0);
	}
	free_data(exec->data);
	if (pid)
		waitpid(pid, &status, 0);
	g_last_val = WEXITSTATUS(status);
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
			if (i == exec->n_pipes && status)
				g_last_val = WEXITSTATUS(status);
		/* ft_printf("i-> %d exit value-> %d\n",i, g_last_val); */
	}
	free_pipes(exec, exec->n_pipes);
	free(exec->pid);
	exec->pid = NULL;
	free_data(exec->data);
	return (0);
}

static void	exec_child(t_exec *exec, int i)
{
	pipe_handler(exec, i); //need correct exit code and free
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

int process_handler(t_exec *exec)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = NULL;
	if (here_doc_handler(exec))
		return (1);
/* 	for (t_data *temp = *(exec->data); temp; temp = temp->next)
		ft_printf("word->%s token->%d\n", temp->word, temp->token); */
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
			return (1);
		if (pids[i] == 0)
		{
			exec_child(exec, i);
		}
	}
	return (parent_close_wait(exec));
}
