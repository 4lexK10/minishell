/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:30:13 by akloster          #+#    #+#             */
/*   Updated: 2024/08/05 06:33:29 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int redir_in() */

/* t_redir	*redir_check(t_data *data, int n_pipes)
{
	int		n_redir;
	int		i;
	t_redir	*redir_data;
	int		*redir;

	n_redir = 0;
	i = 0;
	redir_data = NULL;
	while (n_pipes-- >= 0)
	{
		redir_data = (t_redir *)malloc(sizeof(t_redir) * (n_pipes + 1));
		if (!redir_data)
		{
			ft_error("malloc", NO_EXIT);
			return (NULL);
		}
		while (data && data->token != PIPE)
		{
			if (data->token == H_DOC)
			{
				redir_data->here_doc == true;
				redir_data->stop = data->next->word;
				data = data->next->next;
			}
			else if (data->token == IN)
			{
				redir_data->in = data->next->word;
				data = data->next->next;
			}
			else
			{
				redir_data->here_doc == false;
				redir_data->in == NULL;
				redir_data->stop == NULL;
			}
		}
	}
} */
/*

redir check


< Makefile cat >> EOF | sort > out1


redir_check()


init_redir(t_data **data)

ft_putstr_fd("\n", 2);


*/

static int	extrma_fork(int **pipes, int n_pipes, int last)
{
	/* printf("extrema -> %d %d\n", pipes[i][0], pipes[i][1]); */
	if (last)
	{
		if (dup2(pipes[n_pipes - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		if (close(pipes[n_pipes - 1][1]) == -1)
			return (ft_error("close", NO_EXIT));
		pipe_cleaner(pipes, n_pipes, n_pipes - 1, SINGLE);
	}
	else
	{
		if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		if (close(pipes[0][0]) == -1)
			return (ft_error("close", NO_EXIT));
		pipe_cleaner(pipes, n_pipes, 0, SINGLE);
	}
	return (0);
}

/*
                    stdin  -->  cat   1 | 0    cat   1 | 0  cat   1 | 0  cat --> stdout
*/

int	file_handler(int **pipes, int *pids, int n_pipes)
{
	int	i;

	i = 0;
/* 	for (int i = 0; pids[i]; ++i)
		printf("%d\n", pids[i]); */
	/* printf("end\n"); */
/* 	for (int i = 0; i < n_pipes; ++i)
		printf("w_end: %d r_end %d\n", pipes[i][1], pipes[i][0]); */
	/* write(2, "test\n", 5); */
	if (pids[i] == 0)
	{
		if (extrma_fork(pipes, n_pipes, FIRST)) // WORKS
			return (1);
		return (0);
	}
	else if (pids[n_pipes] > 0)
		return (0);
	while (++i < n_pipes) //n_pipes = 3, 
						 //	i = 1
	{
		if (pids[i] == 0 && pids[i - 1] > 0)
		{
			if (body_fork(i, pipes, n_pipes))
				return (1);
			return (0);
		}
	}
	if (extrma_fork(pipes, n_pipes, LAST))
			return (1);
/* 	if (close_pipes(pipes, n_pipes))
		return (1); */
	return (0);
}

/* static void put_str_fd(char *str) // <<<------- DELETE THIS
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
	itoa()
	
	write(2, &c, 1);
	write(2, "\n", 1);
} 
*/

