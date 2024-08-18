/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:30:13 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 19:11:24 by akloster         ###   ########.fr       */
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
static void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
}
static int	extrma_fork(int **pipes, int n_pipes, int last)
{
	/* printf("extrma -> %d %d\n", pipes[i][0], pipes[i][1]); */
	if (last)
	{
	// READ end
		if (dup2(pipes[n_pipes - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		pipe_cleaner(pipes, n_pipes);
		/* put_str_fd("lasrt"); */
		return (0);
		
	}
	// WRITE end
	if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	/* put_str_fd("first"); */
	return (0);
}

/* read_end()
{
	
} */

static int	body_fork(int i, int **pipes, int n_pipes)
{
// READ end
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
// WRITE END
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	/* put_str_fd("body\n"); */
	return (0);
}

/*
                    stdin  -->  cat   1 | 0    cat   1 | 0  cat   1 | 0  cat --> stdout
*/
void pipe_handler(int n_pipes, int **pipes, int i)
{
	if (i == 0)
	{
		if (extrma_fork(pipes, n_pipes, FIRST))
			exit(1);
	}
	if (i == n_pipes)
	{
		if (extrma_fork(pipes, n_pipes, LAST))
			exit(1);	
	}	
	else if (i != 0 && i != n_pipes)
	{
		if (body_fork(i, pipes, n_pipes))
			exit(1);
	}
}
/* int	pipe_handler(int **pipes, int *pids, int n_pipes, int i)
{
	if (pids[i] > 0) // parent
		return (0);
	if (i == 0)
	{
		if (extrma_fork(pipes, n_pipes, FIRST)) // WORKS
			return (1);
		return (0);
	}
	while (++i < n_pipes)
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
	return (0);
} */

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

