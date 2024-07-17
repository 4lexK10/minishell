/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/17 20:54:23 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	**init_pipes(int n_pipe)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = (int **)malloc(sizeof(int *) * n_pipe);
	if (!pipes)
		ft_error("malloc");
	while (++i < n_pipe)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2); 
		if (!pipes[i])
			free_int_arr(&pipes, i);
		if (pipe(pipes[i]) == -1)
		{
			free_int_arr(&pipes, i + 1);
			ft_error("pipe");
			return (NULL);
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

int	exec(t_data **data)
{
	int	n_pipe;
	int	**pipes;

	n_pipe = pipe_check(data);
	pipes = init_pipes(n_pipe);
	if (!pipes)
	{
		free_data(&data);
		exit(errno);
	}
	executor(n_pipe, data, pipes);
	
}