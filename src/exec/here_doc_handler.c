/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:21:39 by akloster          #+#    #+#             */
/*   Updated: 2024/10/14 17:36:27 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_redir(t_data *temp, char *path)
{
	temp->token = IN;
	free(temp->next->word);
	temp->next->word = ft_strdup(path);
	if (!temp->next->word)
		return (ft_error("malloc", NULL, OG_MSG));
	return (0);
}

int	init_here_doc(char **path, int cnt)
{
	int	fd_Hdoc;
	int	i;

	i = 0;
	if (cnt > 20)
		return (ft_error("too many here_docs", NULL, MY_MSG));
	while (cnt-- > 0)
	{
		++((*path)[19]);
		if ((*path)[19] == '9')
		{
			(*path)[19] = '0';
			++((*path)[18]);
		}
	}
	fd_Hdoc = open(*path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_Hdoc == -1)
		return (ft_error("open: ", *path, OG_MSG));
	return (fd_Hdoc);
}

int	here_doc(char *limiter, char **path, int cnt)
{
	char	*line;
	int		fd_Hdoc;

	fd_Hdoc = init_here_doc(path, cnt);
	if (fd_Hdoc == -1)
		return (1);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (0);
		if (ft_strncmp(line, limiter, (ft_strlen(limiter) + 1)) == '\n')
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putstr_fd(line, fd_Hdoc);
		free(line);
	}
	close(fd_Hdoc);
	return (0);
}

static int	get_here_doc(t_data **data, int *cnt)
{
	t_data	*temp;
	char	*path;

	path = ft_strdup("/tmp/temp_here_doc00");
	if (!path)
		return (ft_error("malloc", NULL, OG_MSG));
	temp = *data;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == H_DOC)
		{
			if (setup_here_doc(temp, &path, *cnt))
				return (1);
		}
		temp = temp->next;
	}
	my_free(&path);
	*data = temp;
	return (0);
}

int	here_doc_handler(t_exec *exec)
{
	t_data *temp;
	int		cmd_i;

	temp = *(exec->data);
	cmd_i = 0;
	while (temp)
	{
		if (get_here_doc(&temp, &cmd_i))
			return (1);
		if (temp && temp->token == PIPE)
			temp = temp->next;
		++cmd_i;
	}
	return (0);
}