/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:00:08 by akloster          #+#    #+#             */
/*   Updated: 2024/09/17 01:12:52 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_env_var(char **env, char *str)
{
	free(*env);
	*env = ft_strdup(str);
	if (!(*env))
		return (ft_error("malloc", NO_EXIT));
	return (0);
}

static int	app_env_var(char **env, char *str)
{
	char	*temp;

	temp = ft_strdup(*env);
	if (!temp)
		return (ft_error("malloc", NO_EXIT));
	free(*env);
	while (*str != '=')
		++str;
	++str;
	*env = ft_strjoin(temp, str);
	free(temp);
	temp = NULL;
	if (!(*env))
		return (ft_error("malloc", NO_EXIT));
	return (0);
}

static int	change_env_var(t_exec *exec, char *str)
{
	char	*var;
	int		i;

	i = 0;
	while (str[i] != '=')
		++i;
	var = (char *)malloc(i + 1);
	if (!var)
		return (ft_error("malloc", NO_EXIT));
	ft_memmove(var, str, i);
	var[i] = '\0';
	i = -1;
	while ((exec->env)[++i])
	{
		if (ft_strncmp((exec->env)[i], var, (ft_strlen(var) + 1)) == '=')
			return (free_arr(&var), create_env_var(&(exec->env)[i], str));
		if (ft_strncmp((exec->env)[i], var, (ft_strlen(var) + 1)) == '+')
			return (free_arr(&var), app_env_var(&(exec->env)[i], str));
	}
	free_arr(&var);
	free_ptr_arr(&(exec->env));
	exec->env = init_env((exec->envp), str);
	if (exec->env)
		return (0);
	return (1);
}

int	ft_export(t_exec *exec, t_data *data)
{
	if (exec->n_pipes)
		return (0);
	if (!data || data->token != STRING)
			return (need_sort_env(exec->env));
	if (ft_strnstr(data->word, "=", ft_strlen(data->word + 1)))
		return (change_env_var(exec, data->word), need_sort_env((exec->env)));
	return (0);
}
