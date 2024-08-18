/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 18:28:03 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int needs_preRedir(t_data *data, int **pipes, int i_cmd, int n_pipes)
{
	int	fd_in;

 	while (data && data->token != IN && data->token != PIPE)
		data = data->next;
	if (!data || data->token == PIPE)
		return (0);
	if (access(data->next->word, R_OK) == -1)
		return (ft_error(data->next->word, NO_EXIT));
	fd_in = open(data->next->word, O_RDONLY);
	ft_printf("pre %s\n", data->next->word);
	if (fd_in == -1)
		return (ft_error("open", NO_EXIT));
	if (i_cmd == 0)
	{
		if (dup2(fd_in, STDIN_FILENO))
			return (ft_error("dup2", NO_EXIT));
	}
	else
	{
		if (dup2(fd_in, pipes[i_cmd - 1][0]) == -1)
			return (ft_error("dup2", NO_EXIT));
	}
	return (0);
}

static int	needs_postRedir(t_data *data, int **pipes, int i_cmd, int n_pipes)
{
	int	fd_out;

 	while (data && data->token != IN && data->token != PIPE)
		data = data->next;
	if (!data || data->token == PIPE)
		return (0);
	if (access(data->next->word, F_OK) == -1)
		fd_out = open(data->next->word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_out == -1)
		return (ft_error("open", NO_EXIT));
	if (i_cmd == n_pipes)
	{
		if (dup2(fd_out, pipes[n_pipes - 1][0] == -1))
			return (ft_error("dup2", NO_EXIT));
	}
	else
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (ft_error("dup2", NO_EXIT));
	}
	return (0);
}

int	redir_check(t_data *data, int **pipes, int i_cmd, int n_pipes)
{
	int		i;

	i = -1;
	while (++i < i_cmd)
	{
		while (data->token != PIPE)
			data = data->next;
	}
	if (needs_preRedir(data, pipes, i_cmd, n_pipes))
		return (1);
	if (needs_postRedir(data, pipes, i_cmd, n_pipes))
		return (1);
	return (0);
}


