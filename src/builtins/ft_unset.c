/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:03:58 by akloster          #+#    #+#             */
/*   Updated: 2024/09/28 04:46:17 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int finish_env(char **temp, t_exec *exec, int j)
{
	temp[j] = NULL;
	free_env(exec);
	exec->env = temp;
	return (0);
}

static int remove_env_var(t_exec *exec, char *var)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while ((exec->env)[i])
		++i;
	temp = (char **)malloc(sizeof(char *) * i);
	if (!temp)
		return (ft_error("malloc", NO_EXIT));
	i = -1;
	j = -1;
	while ((exec->env)[++i])
	{
		if (ft_strncmp((exec->env)[i], var, (ft_strlen(var) + 1)) == '=')
		{
			if (!temp[++i])
				break ;
		}
		temp[++j] = ft_strdup((exec->env)[i]);
		if (!(temp[j]))
			return (free_ptr_arr(&temp), ft_error("malloc", NO_EXIT));
	}
	return (finish_env(temp, exec, ++j));
}

int ft_unset(t_exec *exec, t_data *data)
{
	int		i;

	if (!data || data->token != STRING)
		return (0);
	i = -1;
	while ((exec->env)[++i])
	{
		if (ft_strncmp((exec->env)[i], data->word, (ft_strlen(data->word) + 1)) == '=')
			return (remove_env_var(exec, data->word));
	}
	return (0);
}
