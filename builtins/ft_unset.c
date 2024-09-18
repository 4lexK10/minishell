/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:03:58 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 09:00:28 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int remove_env_var(char ***env, char *var)
{
	int		i;
	char	**temp;

	i = 0;
	temp = *env;
	while ((*env)[i])
		++i;
	*env = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (temp[++i])
	{
		if (ft_strncmp(temp[i], var, (ft_strlen(var) + 1)) == '=')
		{
			ft_printf("remove fct->%s\n", var);
			continue ;
		}
		(*env)[i] = ft_strdup(temp[i]);
		if (!((*env)[i]))
		{
			free_ptr_arr(env);
			free_ptr_arr(&temp);
			return (ft_error("malloc", NO_EXIT));
		}
	}
	(*env)[i] = NULL;
	free_ptr_arr(&temp);
	return (0);
}

int ft_unset(char ***env, t_data *data)
{
	int		i;

	if (!data || data->token != STRING)
		return (0);
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], data->word, (ft_strlen(data->word) + 1)) == '=')
			return (remove_env_var(env, data->word), need_sort_env(*env));
	}
	return (0);
}