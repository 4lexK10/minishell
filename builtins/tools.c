/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:52:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/11 20:26:22 by akloster         ###   ########.fr       */
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
    {
        ft_exit(exec);
    }
    return (res);
}
