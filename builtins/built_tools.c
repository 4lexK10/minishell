/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:52:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/20 15:12:29 by akloster         ###   ########.fr       */
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

int	built_handler(t_exec *exec, char ***env, int i)
{
    t_data	*builtin;
    int		res;

    res = 0;
    builtin = skipTo_cmd(*(exec->data), i);
    builtin = find_built(builtin);
    if (!ft_strncmp(builtin->word, "cd", 3))
        res = ft_cd(env, builtin->next);
    else if (!ft_strncmp(builtin->word, "echo", 5))
        res = ft_echo(builtin->next);
    else if (!ft_strncmp(builtin->word, "exit", 5))
        ft_exit(exec, env);
    else if (!ft_strncmp(builtin->word, "pwd", 4))
        res = ft_pwd();
    else if (!ft_strncmp(builtin->word, "env", 4))
        res = ft_env(*env, builtin->next);
    else if (!ft_strncmp(builtin->word, "export", 7))
        res = ft_export(exec, env, builtin->next);
    else if (!ft_strncmp(builtin->word, "unset", 6))
        res = ft_unset(env, builtin->next);
    return (res);
}

int is_built(t_exec *exec, char ***env, int i)
{
	t_data	*temp;
	int		res;

	temp = skipTo_cmd(*(exec->data), i);
	if (temp->token != BUILT)
		return (-1);
	res = built_handler(exec, env, i);
	free_data(exec->data);
	if (exec->in_pipe)
		free(*(exec->pid));
	free_int_arr(&(exec->pipes), exec->n_pipes);
    return (res);
}
