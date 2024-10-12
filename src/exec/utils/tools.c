/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:50:03 by akloster          #+#    #+#             */
/*   Updated: 2024/10/12 17:14:54 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_int_arr(int ***arr, int sub_arr_nbr)
{
	int	i;

	i = -1;
	if (!arr || !(*arr))
		return ;
	while (++i < sub_arr_nbr)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void pre_exec_free(t_exec *exec)
{
	if (exec->n_pipes > 0)
	{
		free_pipes(exec, exec->n_pipes);
		free(exec->pid);
		exec->pid = NULL;
	}
}

void	free_env(t_exec *exec)
{
	int	i;

	i = -1;
	if (!exec || !(exec->env))
		return ;
	if (*(exec->env))
	{
		while ((exec->env)[++i])
		{
			free((exec->env)[i]);
			(exec->env)[i] = NULL;
		}
	}
	free(exec->env);
	exec->env = NULL;
}

int	add_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (write(STDOUT_FILENO, "=\"", 2) == -1)
				return (1);
		}
		else
			if (write(STDOUT_FILENO, &str[i], 1) == -1)
				return (1);
	}
	if (write(STDOUT_FILENO, "\"\n", 2) == -1)
		return (1);
	return (0);
}

int	setup_here_doc(t_data *temp, char **path, int cnt)
{
	if (!(temp->next))
	{
		my_free(path);
		return (ft_error(
			"syntax error near unexpected token", "'newline'", MY_MSG));
	}
	else if (temp->next->token != STRING)
	{
		my_free(path);
		return (ft_error(
			"syntax error near unexpected token", NULL, temp->next->token));
	}
	if (here_doc(temp->next->word, path, cnt))
	{
		my_free(path);
		return (1);
	}
	if (reset_redir(temp, *path))
	{
		my_free(path);
		return (1);
	}
	return (0);
}
