/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:52:57 by akloster          #+#    #+#             */
/*   Updated: 2024/10/24 14:05:51 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*find_built(t_data *data)
{
	while (data && data->token != PIPE)
	{
		if (data->token == BUILT)
			return (data);
		data = data->next;
	}
	return (NULL);
}

int	built_handler(t_exec *exec, int i)
{
	t_data	*builtin;
	int		res;

	res = 0;
	builtin = skipTo_cmd(*(exec->data), i);
	builtin = find_built(builtin);
	if (!ft_strncmp(builtin->word, "cd", 3))
		res = ft_cd(exec, builtin->next);
	else if (!ft_strncmp(builtin->word, "echo", 5))
		res = ft_echo(exec, builtin->next);
	else if (!ft_strncmp(builtin->word, "exit", 5))
		ft_exit(exec, builtin->next);
	else if (!ft_strncmp(builtin->word, "pwd", 4))
		res = ft_pwd(exec);
	else if (!ft_strncmp(builtin->word, "env", 4))
		res = ft_env(exec, builtin->next);
	else if (!ft_strncmp(builtin->word, "export", 7))
		res = ft_export(exec, builtin->next);
	else if (!ft_strncmp(builtin->word, "unset", 6))
		res = ft_unset(exec, builtin->next);
	if (res && i == exec->n_pipes)
		g_last_val = res;
	return (res);
}

int is_built(t_exec *exec, int i)
{
	t_data	*temp;
	int		res;

	temp = skipTo_cmd(*(exec->data), i);
	if (!temp)
	{
		free_exec(exec);
		exit(0);
	}
	while (temp && temp->token != PIPE && temp->token != BUILT)
		temp = temp->next;
	if (!temp || temp->token != BUILT)
		return (-1);
	res = built_handler(exec, i);
	return (res);
}

void    is_cmd_valid(t_exec *exec, int cmd_i)
{
	t_data *temp;

	temp = skipTo_cmd(*exec->data, cmd_i);
	if (!temp || !temp->word)
	{
		ft_printf("hello\n");
		free_exec(exec);
		exit(0);
	}
}
