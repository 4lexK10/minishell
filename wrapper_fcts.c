/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:17:40 by akloster          #+#    #+#             */
/*   Updated: 2024/08/01 01:18:39 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
	{
		if (close(pipes[i][0]) == -1)
			return (ft_error("close", NO_EXIT));
		if (close(pipes[i][1]) == -1)
			return (ft_error("close", NO_EXIT));
	}
	return (0);
}

int	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error("fork", NO_EXIT);
		return (-1);
	}
	return (pid);
}

int	body_fork(int i, int **pipes, int *pids)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (0);
}
