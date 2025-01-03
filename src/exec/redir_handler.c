/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:55:42 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_data	*go_to_cmd(t_exec *exec, int i_cmd)
{
	int		i;
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

static void	get_next(t_data **temp, int type)
{
	if (type == IN)
	{
		while (*temp && (*temp)->token != IN && (*temp)->token != PIPE)
			*temp = (*temp)->next;
	}
	else
	{
		while (*temp && (*temp)->token != OUT
			&& (*temp)->token != OUT_AP && (*temp)->token != PIPE)
			*temp = (*temp)->next;
	}
}

int	needs_pre_redir(t_exec *exec, int i_cmd)
{
	int		fd_in;
	t_data	*temp;

	temp = go_to_cmd(exec, i_cmd);
	if ((temp && temp->next && temp->next->token >= IN
			&& temp->next->token <= H_DOC) && !temp->next->next)
		return (EXIT_FAILURE);
	get_next(&temp, IN);
	if (!temp || temp->token == PIPE)
		return (-1);
	while (temp && temp->next && temp->token != PIPE)
	{
		if (access(temp->next->word, R_OK) == -1)
			return (ft_error(temp->next->word, NULL, OG_MSG));
		fd_in = open(temp->next->word, O_RDONLY);
		if (fd_in == -1)
			return (ft_error("open: ", temp->next->word, OG_MSG));
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (ft_error("dup2", NULL, OG_MSG));
		if (close(fd_in) == -1)
			return (ft_error("close", NULL, OG_MSG));
		temp = temp->next;
		get_next(&temp, IN);
	}
	return (EXIT_SUCCESS);
}

int	needs_post_redir(t_exec *exec, int i_cmd)
{
	t_data	*temp;
	int		fd_out;

	temp = go_to_cmd(exec, i_cmd);
	if ((temp && temp->next && temp->next->token >= IN
			&& temp->next->token <= H_DOC) && !temp->next->next)
		return (EXIT_FAILURE);
	get_next(&temp, OUT);
	if (!temp || temp->token == PIPE)
		return (-1);
	while (temp && temp->next && temp->token != PIPE)
	{
		fd_out = ft_open(temp->next->word, temp->token);
		if (fd_out == -1)
			return (EXIT_FAILURE);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (ft_error("dup2", NULL, OG_MSG));
		if (close(fd_out) == -1)
			return (ft_error("close", NULL, OG_MSG));
		temp = temp->next;
		get_next(&temp, OUT);
	}
	return (EXIT_SUCCESS);
}
