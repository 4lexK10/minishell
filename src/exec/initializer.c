/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/27 22:49:55 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char **envp, char *new_var)
{
	char	**env;
	int		n_var;

	if (!envp || !(*envp))
		return (NULL);
	n_var = 0;
	while (envp[n_var])
		++n_var;
	if (new_var)
		++n_var;
	env = (char **)malloc(sizeof(char *) * (n_var + 1));
	if (!env)
		return (ft_error("malloc", NO_EXIT), NULL);
	n_var = -1;
	if (new_var)
	{
		env[++n_var] = ft_strdup(new_var);
		if (!env[n_var])
		{
			free_ptr_arr(&env);
			return (ft_error("malloc", NO_EXIT), NULL);
		}
	}
	return (fill_env(envp, &env, n_var));
}

static void init_exec(t_exec *exec, t_data **data, int n_pipes, int **pipes)
{
	t_exec	*exec;

	exec->data = data;
	exec->n_pipes = n_pipes;
	exec->pipes = pipes;
	exec->pid = NULL;
	exec->std_in = dup(STDIN_FILENO);
	exec->std_out = dup(STDOUT_FILENO);
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

int	initializer(t_exec *exec, t_data **data, char **envp)
{
	int		n_pipes;
	int		**pipes;
	t_exec	*exec;

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
	init_exec(data, n_pipes, pipes, envp);
	exec->env = init_env(envp, NULL);
	if (!(exec->env))
		return (1);
	return (process_handler(exec));
}
