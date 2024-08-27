/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/08/19 19:50:04 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*init_exec(t_data **data, int n_pipes, int **pipes, char **envp)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->data = data;
	exec->envp = envp;
	exec->n_pipes = n_pipes;
	exec->pipes = pipes;
	exec->std_in = dup(0);
	exec->std_out = dup(1);
	if (exec->std_in == -1 || exec->std_in == -1)
		return (ft_error("dup", NO_EXIT), NULL);
	return (exec);
}

static int	**init_pipes(int n_pipes)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = (int **)malloc(sizeof(int *) * n_pipes);
	if (!pipes)
		ft_error("malloc", NEED_EXIT);  // BAD EXIT NEEDS t_data free !!!!
	while (++i < n_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			free_int_arr(&pipes, i);
		if (pipe(pipes[i]) == -1)
		{
			free_int_arr(&pipes, i + 1);
			ft_error("pipe", NEED_EXIT); // BAD EXIT NEEDS t_data free !!!!
		}
	}
	return (pipes);
}

int	pipe_check(t_data **data)
{
	t_data	*temp;
	int		cnt;

	temp = *data;
	cnt = 0;
	while (temp)
	{
		if (temp->token == PIPE) // needs correctiom: pipe token number
			++cnt;
		temp = temp->next;
	}
	return (cnt);
}

int	execution(t_data **data, char **envp)
{
	int		n_pipes;
	int		**pipes;
	t_exec	*exec;

	pipes = NULL;
	n_pipes = pipe_check(data);
	/* printf("n_pipe = %d\n", n_pipes); */
	if (n_pipes > 0)
	{
		pipes = init_pipes(n_pipes);
		if (!pipes)
		{
			free_data(data);
			exit(1);
		}
	}
	exec = init_exec(data, n_pipes, pipes, envp);
	executor(exec);
	free_int_arr(&pipes, n_pipes);
	free(exec);
	/* exit(1);  // MAYBE EXIT LATER? */
	return (0);
}
