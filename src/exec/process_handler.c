/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/10/24 12:46:48 by akiener          ###   ########.fr       */
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
	int		status;

	pid = 0;
	status = 0;
	
	if (!find_built(*(exec->data)))
	{
		pid = fork();
		if (pid == -1)
			return (ft_error("fork", NULL, OG_MSG));
	}
	if (pid == 0)
	{
		if (needs_pre_redir(exec, 0) == 1 || needs_post_redir(exec, 0) == 1)
			return (1);
		is_cmd_valid(exec, 0);
		executioner(exec, 0);
	}
	free_data(exec->data);
	if (pid)
	{
		waitpid(pid, &status, 0);
		g_last_val = WEXITSTATUS(status);
	}
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
	signal(SIGINT, SIG_DFL);
	pipe_handler(exec, i); //need correct exit code and free
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

int process_handler(t_exec *exec)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = NULL;
	if (here_doc_handler(exec))
		return (1);
/* 	ft_printf("\n AFTER HEREDOC\n");
	for (t_data *temp = *(exec->data); temp; temp = temp->next)
		ft_printf("|%s|   %d\n", temp->word, temp->token); */
	if (exec->n_pipes == 0)
		return (no_pipe_exec(exec));
	pids = init_pids(exec->n_pipes);
	if (!pids)
		return (1);
	exec->pid = pids;
	while (++i <= exec->n_pipes)
	{
/* 		sigaction(SIGQUIT, SIG_DFL, NULL);
		sigaction(SIGINT, SIG_DFL, NULL); */
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_error("fork", NULL, OG_MSG));
		if (pids[i] == 0)
			exec_child(exec, i);
	}
	return (parent_close_wait(exec));
}
