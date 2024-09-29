/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/29 17:54:04 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_exec *exec, char **envp)
{
	int		i;

	if (!envp || !(*envp))
		return ;
	i = 0;
	while (envp[i])
		++i;
	exec->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(exec->env) && ft_error("malloc", NO_EXIT))
		return ;
	i = -1;
	while (envp[++i])
	{
		(exec->env)[i] = ft_strdup(envp[i]);
		if (!(exec->env)[i])
		{
			free_env(exec);
			ft_error("malloc", NO_EXIT);
			return ;
		}
	}
	(exec->env)[i] = NULL;
}

static void init_exec(t_exec *exec, t_data **data, int n_pipes, int **pipes)
{
	exec->data = data;
	exec->n_pipes = n_pipes;
	exec->pipes = pipes;
	exec->pid = NULL;
	exec->std_in = dup(STDIN_FILENO);
	exec->std_out = dup(STDOUT_FILENO);
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

int	initializer(t_exec *exec, t_data **data)
{
	int		n_pipes;
	int		**pipes;

	pipes = NULL;
	n_pipes = pipe_check(data);
	if (n_pipes > 0)
	{
		pipes = init_pipes(n_pipes);
		if (!pipes)
		{
			free_data(data);
			exit(1);
		}
	}
	init_exec(exec, data, n_pipes, pipes);
	return (process_handler(exec));
}
