/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/09/05 03:22:49 by akloster         ###   ########.fr       */
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

static int	limit_check(char *limiter, char *line)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
	{
		if (line[ft_strlen(limiter)] == '\n')
			return (1);
	}
	return (0);
}

static int	here_doc(t_exec *exec, int i_cmd, char *limiter)
{
	char	*line;
	int		fd_Hdoc;

	fd_Hdoc = open("/tmp/temp_here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_Hdoc == -1)
		return (ft_error("open", NO_EXIT));
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (-1);
		if (limit_check(limiter, line))
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putstr_fd(line, fd_Hdoc);
		free(line);
	}
	close(fd_Hdoc);
	fd_Hdoc = open("/tmp/temp_here_doc", O_RDONLY);
	dup2(fd_Hdoc, STDIN_FILENO);
	close(fd_Hdoc);
	return (EXIT_SUCCESS);
}

int needs_preRedir(t_exec *exec, int i_cmd)
{
	int		fd_in;
	t_data	*temp;

	temp = redir_check(exec, i_cmd);
 	while (temp && temp->token != IN && temp->token != PIPE && temp->token != H_DOC)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (-1);
	if (temp->token == H_DOC)
	{
		fd_in = here_doc(exec, i_cmd, temp->next->word);
		if (fd_in == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (access(temp->next->word, R_OK) == -1)
		return (ft_error(temp->next->word, NO_EXIT));
	fd_in = open(temp->next->word, O_RDONLY);
/* 	ft_printf("pre |%s|\n", temp->next->word); */
	if (fd_in == -1)
		return (ft_error("open", NO_EXIT));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	close(fd_in);
	return (EXIT_SUCCESS);
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
	/* ft_printf("file |%s| type %d\n", temp->next->word, temp->token); */
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
