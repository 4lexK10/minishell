/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:30:13 by akloster          #+#    #+#             */
/*   Updated: 2024/08/21 23:21:22 by akloster         ###   ########.fr       */
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

static int	extrma_fork(t_exec *exec, int last) // factorise into two function calls ?
{
	int	in_check;
	int	out_check;

	if (last)
	{
		in_check = needs_preRedir(exec, exec->n_pipes);
		out_check = needs_postRedir(exec, exec->n_pipes);
/* 		ft_printf("LAST pre: %d post: %d\n", in_check, out_check); */
		if (in_check == FOUND)
			return (FOUND);
		if (in_check == FAILED || out_check == FAILED)
			return (FAILED);
		if (dup2((exec->pipes)[exec->n_pipes - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		return (EXIT_SUCCESS);
	}
	in_check = needs_preRedir(exec, 0);
	out_check = needs_postRedir(exec, 0);
/* 	ft_printf("FIRST pre: %d post: %d\n", in_check, out_check); */
	if (in_check == FAILED || out_check == FAILED)
		return (FAILED);
	if (out_check == FOUND)
		return (FOUND);
/* 	ft_printf("exec->pipes[0] [%d, %d]\n",(exec->pipes)[0][0] , (exec->pipes)[0][1]); */
/* 	for (char *out = get_next_line((exec->pipes)[0][1]); ft_printf("%s", out), out; out = get_next_line((exec->pipes)[0][1]))
		ft_printf("inside pipe |%s|\n", out); */
	if (dup2((exec->pipes)[0][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (0);
}

/* read_end()
{
	
} */

static int	body_fork(int i, t_exec *exec)
{
	int	in_check;
	int	out_check;

	in_check = needs_preRedir(exec, i);
	out_check = needs_postRedir(exec, i);
	if (in_check == FAILED || out_check == FAILED)
		return (FAILED);
	if (in_check == FOUND)
	{
		if (dup2((exec->pipes)[i][1], STDOUT_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		return (EXIT_SUCCESS);
	}
	if (out_check == FOUND)
	{
		if (dup2((exec->pipes)[i - 1][0], STDIN_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
		return (EXIT_SUCCESS);
	}
	if (dup2((exec->pipes)[i][1], STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	if (dup2((exec->pipes)[i - 1][0], STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (EXIT_SUCCESS);
}

/*
                    stdin  -->  cat   1 | 0    cat   1 | 0  cat   1 | 0  cat --> stdout
*/
void pipe_handler(t_exec *exec, int i)
{
	
	if (i == 0)
	{
		if (extrma_fork(exec, FIRST))
			exit(1);
	}
	else if (i == exec->n_pipes)
	{
		if (extrma_fork(exec, LAST))
			exit(1);	
	}	
	else
	{
		if (body_fork(i, exec))
			exit(1);
	}
	pipe_cleaner(exec->pipes, exec->n_pipes);
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

