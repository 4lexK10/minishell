/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/08/20 03:13:15 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int needs_preRedir(t_data *temp, t_exec *exec, int i_cmd)
{
	int		fd_in;

 	while (temp && temp->token != IN && temp->token != PIPE)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (-1);
	if (access(temp->next->word, R_OK) == -1)
		return (ft_error(temp->next->word, NO_EXIT));
	fd_in = open(temp->next->word, O_RDONLY);
	ft_printf("pre |%s|\n", temp->next->word);
	if (fd_in == -1)
		return (ft_error("open", NO_EXIT));
	if (i_cmd == 0)
	{
		if (dup2(fd_in, STDIN_FILENO))
			return (ft_error("dup2", NO_EXIT));
	}
	else
	{
		ft_printf("---hellp\n");
		if (dup2(fd_in, (exec->pipes)[i_cmd - 1][0]) == -1)
			return (ft_error("dup2", NO_EXIT));
	}
	return (EXIT_SUCCESS);
}

static int	needs_postRedir(t_data *temp, t_exec *exec, int i_cmd)
{
	int		fd_out;

	while (temp && temp->token != OUT && temp->token != PIPE)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (-1);
/* 	ft_printf("|%s|\n", temp->next->word); */
	if (access(temp->next->word, F_OK) == -1)
		fd_out = open(temp->next->word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_out == -1)
		return (ft_error("open", NO_EXIT));
	if (i_cmd == exec->n_pipes)
	{
		if (dup2(fd_out, (exec->pipes)[exec->n_pipes - 1][0] == -1))
			return (ft_error("dup2", NO_EXIT));
	}
	else
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
	}
	return (EXIT_SUCCESS);
}

static int	redir_cleanUp(int pre, int in, t_exec *exec, int i_cmd)
{
	if (pre == 0)
		
}

int	redir_check(t_exec *exec, int i_cmd)
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
	/* ft_printf("temp->next %s\n", temp->next->word); */
	pre = needs_preRedir(temp, exec, i_cmd);
	post = needs_postRedir(temp, exec, i_cmd);
	return (redir_cleanUp(pre, post, exec, i_cmd));
}


