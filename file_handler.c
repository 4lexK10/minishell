/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:30:13 by akloster          #+#    #+#             */
/*   Updated: 2024/07/30 22:44:39 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int redir_in() */

static int	extrma_fork(int i, int **pipes, int last)
{
	if (last)
	{
		/* printf("extrema -> %d %d\n", pipes[i][0], pipes[i][1]); */
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		if (close(pipes[i - 1][1]) == -1)
			return (ft_error("close", NO_EXIT));
	}
	else
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		if (close(pipes[i][0]) == -1)
			return (ft_error("close", NO_EXIT));
	}
	return (0);
}

/*
                    stdin  -->  cat   1 | 0    cat   1 | 0  cat   1 | 0  cat --> stdout
*/


static int	body_fork(int i, int **pipes, int *pids)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (0);
}

/* void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
} */

/* void put_int_fd(int nbr) // <<<------- DELETE THIS
{
	char c;

	nbr = nbr + 48;
	c = (int) nbr;
	write(2, &c, 1);
	write(2, "\n", 1);
} */



int	file_handler(int *pids, int **pipes, int n_pipe)
{
	int	i;

	i = 0;
/* 	for (int i = 0; pids[i]; ++i)
		printf("%d\n", pids[i]); */
	/* printf("end\n"); */
/* 	for (int i = 0; i < n_pipe; ++i)
		printf("w_end: %d r_end %d\n", pipes[i][1], pipes[i][0]); */
	/* write(2, "test\n", 5); */
	if (pids[i] == 0)
	{
		if (extrma_fork(i, pipes, FIRST)) // WORKS
			return (1);
		return (0);
	}
	else if (pids[n_pipe] > 0)
		return (0);
	while (++i < n_pipe) //n_pipe = 3, 
						 //	i = 1
	{
		if (pids[i] == 0 && pids[i - 1] > 0)
		{
			if (body_fork(i, pipes, pids))
				return (1);
			return (0);
		}
	}
	if (extrma_fork(i, pipes, LAST))
			return (1);
/* 	if (close_pipes(pipes, n_pipe))
		return (1); */
	return (0);
}
/*

            
				                      

*/
