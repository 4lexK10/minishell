/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:00:08 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 16:48:01 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_env_var(char **env, char *str)
{
	free(*env);
	*env = ft_strdup(str);
	if (!(*env))
		return (ft_error("malloc", NULL, OG_MSG));
	return (0);
}

static int	app_env_var(char **env, char *str)
{
	char	*temp;

	temp = ft_strdup(*env);
	if (!temp)
		return (ft_error("malloc", NULL, OG_MSG));
	free(*env);
	while (*str != '=')
		++str;
	++str;
	*env = ft_strjoin(temp, str);
	free(temp);
	temp = NULL;
	if (!(*env))
		return (ft_error("malloc", NULL, OG_MSG));
	return (0);
}

static int	create_env_var(t_exec *exec, char *str)
{
	char	**temp;
	int		i;

	i = 0;
	while (exec->env[i])
		++i;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (ft_error("malloc", NULL, OG_MSG));
	i = -1;
	while (exec->env[++i])
	{
		temp[i] = ft_strdup(exec->env[i]);
		if (!temp[i])
			return (free_ptr_arr(&temp), ft_error("malloc", NULL, OG_MSG));
	}
	temp[i] = ft_strdup(str);
	if (!temp[i])
		return (free_ptr_arr(&temp), ft_error("malloc", NULL, OG_MSG));
	temp[i + 1] = NULL;
	free_env(exec);
	exec->env = temp; 
	return (0);
}

int	change_env_var(t_exec *exec, char *str, int (*f)(char **, char *))
{
	char	*var;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '+')
		++i;
	var = (char *)malloc(i + 1);
	if (!var)
		return (ft_error("malloc", NULL, OG_MSG));
	ft_memmove(var, str, i);
	var[i] = '\0';
	i = -1;
	while ((exec->env)[++i])
	{
		if (ft_strncmp((exec->env)[i], var, (ft_strlen(var) + 1)) == '=')
			return (my_free(&var), f(&((exec->env)[i]), str));
	}
	my_free(&var);
	create_env_var(exec, str);
	return (1);
}

int	ft_export(t_exec *exec, t_data *data)
{
	if (exec->n_pipes)
		return (0);
	if (!data || data->token != STRING)
			return (need_sort_env(exec));
	if (ft_strnstr(data->word, "+=", ft_strlen(data->word + 1)))
		return (change_env_var(exec, data->word, app_env_var));
	else if (ft_strnstr(data->word, "=", ft_strlen(data->word + 1)))
		return (change_env_var(exec, data->word, swap_env_var));
	return (0);
}
