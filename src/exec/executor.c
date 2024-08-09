/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/08/09 14:18:02 by akloster         ###   ########.fr       */
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
	pids = (int *)malloc((n_fork + 1) * sizeof(int)); //     n + 1 ---> n childs (execs) + 1 parent
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

	if (data != NULL)
	{
		pids = forker(0);
		if (!pids)
		{
			free_data(data);
			exit(1);
		}
		/* printf("%d %d %d\n", pids[0], pids[1], pids[2]); */
	}
	if (pids[0] == 0)
	{
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
	if (pipe_cleaner(pipes, n_pipes, -1, 0))
		return (1);
/* 	while (wait(NULL) > 0)
		; */
	while (++i <= n_pipes)
	{
		waitpid(pids[i], NULL, 0);
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
	/* redir_check(); */
 //GOOD ,but needs error managment for failed fork()
	/* printf("n_pipes = %d\n", n_pipes); */
/* 	printf("pid[0] = %d\n", pids[0]); */
	
	if (n_pipes)
	{
		pids = forker(n_pipes);
		if (!pids)
		{
			free_data(data);
			exit(1);
		}
		/* printf("[%d %d] [%d %d]\n",pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]); */
		/* printf("%d %d %d\n", pids[0], pids[1], pids[2]); */
		if (pipe_handler(pipes, pids, n_pipes)) //PRBLEM
			return (1);
		while (++i <= n_pipes)
		{
			if (pids[i] == 0) // GOOD
			{
				run_cmd(data, envp, i);
				exit(1);
			}
		}
		if (pids[n_pipes] > 0)
			return (parent_close_wait(pipes, pids, n_pipes));
	}
	else
		return (no_pipe_exec(data, envp));
	return (0);
}
