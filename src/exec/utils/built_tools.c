/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:52:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/27 22:50:06 by akloster         ###   ########.fr       */
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

    res = 0;
    builtin = skipTo_cmd(*(exec->data), i);
    builtin = find_built(builtin);
    if (!ft_strncmp(builtin->word, "cd", 3))
        res = ft_cd(exec, builtin->next);
    else if (!ft_strncmp(builtin->word, "echo", 5))
        res = ft_echo(exec, builtin->next);
    else if (!ft_strncmp(builtin->word, "exit", 5))
        ft_exit(exec);
    else if (!ft_strncmp(builtin->word, "pwd", 4))
        res = ft_pwd(exec);
    else if (!ft_strncmp(builtin->word, "env", 4))
        res = ft_env(exec, builtin->next);
    else if (!ft_strncmp(builtin->word, "export", 7))
        res = ft_export(exec, builtin->next);
    else if (!ft_strncmp(builtin->word, "unset", 6))
        res = ft_unset(exec->env, builtin->next);
    return (res);
}

int is_built(t_exec *exec, int i)
{
	t_data	*temp;
	int		res;

	temp = skipTo_cmd(*(exec->data), i);
	if (temp->token != BUILT)
		return (-1);
	res = built_handler(exec, i);
    return (res);
}
