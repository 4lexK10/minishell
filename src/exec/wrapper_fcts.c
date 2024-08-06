/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:17:40 by akloster          #+#    #+#             */
/*   Updated: 2024/08/06 05:33:20 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_cleaner(int **pipes, int n_pipes, int i_skip, int skip_2x)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
	{
		if (i == i_skip)
		{
			if (skip_2x)
				i += 2;
			else
				++i;
			continue ;
		}
/* 		ft_putnbr_fd(pipes[i][0], 2);
		ft_putstr_fd("\n", 2);
		ft_putnbr_fd(pipes[i][1], 2);
		ft_putstr_fd("\n", 2); */
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


