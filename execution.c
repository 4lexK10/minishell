/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/18 21:32:03 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**init_pipes(int n_pipe)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = (int **)malloc(sizeof(int *) * n_pipe);
	if (!pipes)
		ft_error("malloc", NEED_EXIT);
	while (++i < n_pipe)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2); 
		if (!pipes[i])
			free_int_arr(&pipes, i);
		if (pipe(pipes[i]) == -1)
		{
			free_int_arr(&pipes, i + 1);
			ft_error("pipe", NEED_EXIT);
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
		if (temp->token == 1) // needs correctiom: pipe token number
			++cnt;
		temp = temp->next;
	}
	return (cnt);
}

int	exec(t_data **data, char **envp)
{
	int	n_pipe;
	int	**pipes;

	pipes = NULL;
	n_pipe = pipe_check(data);
	if (n_pipe > 0)
	{
		pipes = init_pipes(n_pipe);
		if (!pipes)
		{
			free_data(data);
			exit(errno);
		}
	}
	if (executor(n_pipe, data, pipes, envp))
	{
		free_int_arr(&pipes, n_pipe);
		exit(errno);
	}
	return (1);
}
