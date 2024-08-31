/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/08/31 23:56:38 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_data	*redir_check(t_exec *exec, int i_cmd)
{
	int		i;
	int		pre;
	int		post;
	t_data	*temp;

	i = -1;
	temp = *(exec->data);
	while (++i < i_cmd)
	{
		while (temp->token != PIPE)
			temp = temp->next;
		temp = temp->next;
	}
	return (temp);
}

int needs_preRedir(t_exec *exec, int i_cmd)
{
	int		fd_in;
	t_data	*temp;

	temp = redir_check(exec, i_cmd);
 	while (temp && temp->token != IN && temp->token != PIPE)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (-1);
	if (access(temp->next->word, R_OK) == -1)
		return (ft_error(temp->next->word, NO_EXIT));
	fd_in = open(temp->next->word, O_RDONLY);
/* 	ft_printf("pre |%s|\n", temp->next->word); */
	if (fd_in == -1)
		return (ft_error("open", NO_EXIT));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (EXIT_SUCCESS);
}

static int	ft_open(char *outfile, int type)
{
	int output;

	//access functions SAFETY!!!!
	if (access(outfile, F_OK) == -1)
		output = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == OUT_ADD)
		output = open(outfile, O_APPEND | O_WRONLY);
	else
		output = open(outfile, O_WRONLY);
	if (output == -1)
	{
		ft_error(outfile, NO_EXIT);
		return (-1);
	}
	return (output);
}

int	needs_postRedir(t_exec *exec, int i_cmd)
{
	t_data *temp;
	int		fd_out;

	temp = redir_check(exec, i_cmd);
	while (temp && temp->token != OUT && temp->token != OUT_ADD && temp->token != PIPE)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (-1);
	ft_printf("file |%s| type %d\n", temp->next->word, temp->token);
/* 	if (access(temp->next->word, F_OK) == -1)
		fd_out = ft_open(temp->next->word, temp->token);
	else if (access(temp->next->word, W_OK) == -1)
		return (ft_error(temp->next->word, NO_EXIT)); */
/* 	ft_printf("post|%s| i_cmd = %d fd_out = %d\n", temp->next->word, i_cmd, fd_out); */
	fd_out = ft_open(temp->next->word, temp->token);
	if (fd_out == -1)
		return (1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	if (close(fd_out) == -1)
		return(ft_error("close", NO_EXIT));
	return (EXIT_SUCCESS);
}




