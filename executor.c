/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/08/01 01:47:57 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int  piper(t_data **node)
{
	if ((*node)->token == 2) // needs correctiom: pipe token number
	{
		*node = (*node)->next;
		redir_in((*node)->word);
	}
	
} */

// forker ----- needs a check if forks are needed before calling forker()

static int	*forker(int n_fork)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (int *)malloc((n_fork + 1) * sizeof(int)); //     n + 1 for n childs (execs) + 1 parent
	if (!pids)
		return (NULL);
	while (++i <= n_fork)
		pids[i] = 0;
	i = 0;
	pids[i] = ft_fork();
	while (++i <= n_fork)
	{
		if (pids[i - 1] > 0)
			pids[i] = ft_fork();
	}
	if (pids[i] == -1) // error managment for children: all pids before are > 0
		return (pids);
	return (pids);
}

static void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
}

/* no_pipe_exec(t_data, char **envp)
{
	t_pid	pid;

	pid = ft_fork();
	if (pid == 0)
		run_cmd(data, get_cmd(data, i), envp);
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0)
} */



static int	no_pipe_exec(t_data **data, char **envp, int *pids)
{
	if (pids[0] == 0)
	{
		run_cmd(data, envp, 0);
		exit(1);
	}
	if (waitpid(pids[0], NULL, 0) == -1)
		return (ft_error("waitpid", NO_EXIT));
	return (0);
}

static int	parent_close_wait(int **pipes, int *pids, int n_pipe)
{
	int	i;

	i = -1;
	if (close_pipes(pipes, n_pipe))
		return (1);
	while (++i <= n_pipe) // maybe not
	{
		if (waitpid(pids[i], NULL, 0) == -1)
			return (ft_error("waitpid", NO_EXIT));
	}
	return (0);
}

int executor(int n_pipe, t_data **data, int **pipes, char **envp)
{
	t_data	*temp;
	pid_t	*pids;
	int		i;

	i = -1;
	temp = *data;
	pids = forker(n_pipe); //GOOD ,but needs error managment for failed fork()
/* 	printf("n_pipe = %d\n", n_pipe);
	printf("pid[0] = %d\n", pids[0]); */
	if (!pids)
	{
		free_data(data);
		exit(1);
	}
	if (n_pipe)
	{
		/* printf("%d %d %d %d\n", pids[0], pids[1], pids[2], pids[3]); */
		if (file_handler(pids, pipes, n_pipe)) //PRBLEM
			return (1);
		while (++i <= n_pipe)
		{
			if (pids[i] == 0) // GOOD
			{
				run_cmd(data, envp, i);
				exit(1);
			}
		}
		if (pids[n_pipe] > 0)
			return (parent_close_wait(pipes, pids, n_pipe));
	}
	else
		return (no_pipe_exec(data, envp, pids));	
	return (0);
}
