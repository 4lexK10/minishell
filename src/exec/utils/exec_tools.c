/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:03:07 by akloster          #+#    #+#             */
/*   Updated: 2024/10/14 21:19:43 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*skipTo_cmd(t_data *temp, int cmd_i)
{
	while (cmd_i-- > 0)
	{
		while (temp && temp->token != PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	if (temp && temp->token == IN)
	{
		if (temp->next->next && temp->next->next->token != PIPE)
			temp = temp->next->next;
		else
			return (NULL);
	}
	return (temp);
}

int	cnt_words(t_data *temp)
{
	int		cnt;

	cnt = 0;
	while (temp && temp->word)
	{
		++cnt;
		temp = temp->next;
	}
	return (cnt);
}

void	converter(t_data **data)
{
	t_data *temp;

	temp = *data;
	while (temp)
	{
		if (temp->token >= PIPE && temp->token <= H_DOC)
		{
			free(temp->word);
			temp->word = NULL;
		}
		if (temp->token == NUMBER)
			temp->token = STRING;
		temp = temp->next;
	}
}

void	exec_fail(t_exec *exec, char **path)
{
	free_exec(exec);
	my_free(path);
	ft_error("execve", NULL, OG_MSG);
	exit(errno);
}

int	absolute_cmd_handler(t_exec *exec, int i)
{
	char	**cmd;
	t_data	*temp;
	char	*path;

	temp = skipTo_cmd(*exec->data, i);
	if (temp->token != ABS_PATH)
		return (-1);
	cmd = get_cmd(exec->data, i);
	if (!cmd)
		return (free_exec(exec));
	if (temp && !ft_strncmp(temp->word, "./minishell", 12))
		path = "/Users/akloster/Documents/minishell/./minishell";
	else
		path = temp->word;
	if (access(path, X_OK))
	{
		free_exec(exec);
		ft_error(path, ": No such file or directory", MY_MSG);
		exit(127);
	}
	execve(path, cmd, exec->env);
	exec_fail(exec, NULL);
	return (1);
}
