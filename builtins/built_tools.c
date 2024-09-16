/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:52:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/16 21:24:50 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*find_built(t_data *data)
{
    while (data)
    {
        if (data->token == BUILT)
            break ;
        data = data->next;
    }
    if (data)
        return (data);
    return (NULL);
}

int	built_handler(t_exec *exec, int i)
{
    t_data	*builtin;
    int		res;

    builtin = skipTo_cmd(*(exec->data), i);
    builtin = find_built(builtin);
    if (!strncmp(builtin->word, "cd", 3))
        res = ft_cd(builtin->next, false);
    else if (!strncmp(builtin->word, "echo", 5))
        res = ft_echo(builtin->next);
    else if (!strncmp(builtin->word, "exit", 5))
        ft_exit(exec);
    else if (!strncmp(builtin->word, "pwd", 4))
        res = ft_pwd(builtin->next);
    else if (!strncmp(builtin->word, "env", 4))
        res = ft_env(exec, builtin->next);
    else if (!strncmp(builtin->word, "export", 7))
        res = ft_export(exec, builtin->next);
    return (res);
}

void	is_built(t_exec *exec, int i)
{
	t_data	*temp;
	int		res;

	temp = skipTo_cmd(*(exec->data), i);
	if (temp->token != BUILT)
		return ;
	res = built_handler(exec, i);
	free_data(exec->data);
	if (exec->in_pipe)
		free(*(exec->pid));
	free_int_arr(&(exec->pipes), exec->n_pipes);
	exit(res);
}
