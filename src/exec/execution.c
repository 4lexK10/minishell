/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/08/12 05:09:27 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	pipe_check(t_data **data)
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

int	exec(t_data **data, char **envp)
{
	int	n_pipes;
	int	**pipes;

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
	executor(n_pipes, data, pipes, envp);
	free_int_arr(&pipes, n_pipes);
	/* exit(1);  // MAYBE EXIT LATER? */
	return (0);
}
