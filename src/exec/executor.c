/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 19:11:42 by akloster         ###   ########.fr       */
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

static bool parent_pid_check(int *pids, int i)
{
	while (i >= 0)
	{
		if (pids[0] == 0)
			return (false);
	}
	return (true);
}
/*
 1.          parent --> child1
			997 0 0     0  0  0	
2.          parent --> child2
		    997 998 0   997  0  0

3.          parent --> child 3
		 997 998 999   997 998 0
*/

static int	*init_pids(int n_pipes)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (int *)malloc((n_pipes + 1) * sizeof(int)); //     n + 1 ---> n childs (execs) + 1 parent
	if (!pids)
		return (NULL);
	while (++i <= n_pipes)
		pids[i] = 0;
/* 	i = 0;
 	pids[i] = ft_fork();
	while (++i <= n_fork)
	{
		if (pids[i - 1] > 0parent_pid_check(pids, i - 1) == true)
			pids[i] = ft_fork();
	}
	if (pids[i] == -1) // error managment for children: all pids before are > 0
		return (pids); */
	return (pids);
}

/* static void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
} */

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



static int	no_pipe_exec(t_data **data, char **envp)
{
	int	*pids;

	pids = init_pids(0);
	if (!pids)
	{
		free_data(data);
		exit(1);
	}
		/* printf("%d %d %d\n", pids[0], pids[1], pids[2]); */
	pids[0] = fork();
	if (pids[0] == -1)
		exit(1);
	if (pids[0] == 0)
	{
		/* redir_check() */
		run_cmd(data, envp, 0);
		exit(1);
	}
	if (waitpid(pids[0], NULL, 0) == -1)
		return (ft_error("waitpid", NO_EXIT));
	return (0);
}

static int	parent_close_wait(int **pipes, int *pids, int n_pipes)
{
	int	i;

	i = -1;
	if (pipe_cleaner(pipes, n_pipes))
		return (1);
/* 	while (wait(NULL) > 0)
		; */
	while (++i <= n_pipes)
	{
		waitpid(-1, NULL, 0);

	}
	return (0);
}

void put_int_fd(int nbr) // <<<------- DELETE THIS
{
	char c;

	nbr = nbr + 48;
	c = (int) nbr;
	write(2, &c, 1);
	write(2, "\n", 1);
}

int executor(int n_pipes, t_data **data, int **pipes, char **envp)
{
	t_data	*temp;
	pid_t	*pids;
	int		i;

	i = -1;
	temp = *data;
	pids = init_pids(n_pipes);
	if (!pids)
		return (1);
	if (n_pipes == 0)
		return (no_pipe_exec(data, envp));
	while (++i <= n_pipes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] > 0)
			continue ;
		pipe_handler(n_pipes, pipes, i);
		if (redir_check(*data, pipes, i, n_pipes))
			exit(1);
		pipe_cleaner(pipes, n_pipes);
		run_cmd(data, envp, i);
		exit(1);
	}
	if (parent_close_wait(pipes, pids, n_pipes))
		return (1);
	return (0);
}
