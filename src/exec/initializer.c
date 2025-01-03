/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 17:03:57 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_exec *exec, char **envp)
{
	int		i;

	if (!envp || !(*envp))
		return (1);
	i = 0;
	while (envp[i])
		++i;
	exec->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(exec->env) && ft_error("malloc", NULL, OG_MSG))
		return (1);
	i = -1;
	while (envp[++i])
	{
		(exec->env)[i] = ft_strdup(envp[i]);
		if (!(exec->env)[i])
		{
			free_env(exec);
			return (ft_error("malloc", NULL, OG_MSG));
		}
	}
	(exec->env)[i] = NULL;
	return (incr_shlvl(exec));
}

static void	init_exec(t_exec *exec, t_data **data, int n_pipes, int **pipes)
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
		ft_error("malloc", NULL, OG_MSG);
	while (++i < n_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (pipe_cleaner(pipes, i), free_int_arr(&pipes, i), NULL);
		if (pipe(pipes[i]) == -1)
		{
			pipe_cleaner(pipes, i);
			free_int_arr(&pipes, i + 1);
			ft_error("pipe", NULL, OG_MSG);
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
		if (temp->token == PIPE)
			++cnt;
		temp = temp->next;
	}
	return (cnt);
}

int	initializer(t_exec *exec, t_data **data, struct sigaction *act)
{
	int		n_pipes;
	int		**pipes;

	pipes = NULL;
	n_pipes = pipe_check(data);
	if (n_pipes > 0)
	{
		pipes = init_pipes(n_pipes);
		if (!pipes)
			return (free_data(data), 1);
	}
	init_exec(exec, data, n_pipes, pipes);
	exec->act = *act;
	return (process_handler(exec));
}
