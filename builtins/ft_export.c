/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:00:08 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 08:39:37 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	swap_env_var(char **env, char *str)
{
	ft_printf("in-> create_env_var\n");
	free(*env);
	*env = ft_strdup(str);
	if (!(*env))
		return (ft_error("malloc", NO_EXIT));
	return (0);
}

static int	app_env_var(char **env, char *str)
{
	char	*temp;

	ft_printf("in-> app_env_var\n");
	temp = ft_strdup(*env);
	if (!temp)
		return (ft_error("malloc", NO_EXIT));
	free(*env);
	while (*str != '=')
		++str;
	++str;
	*env = ft_strjoin(temp, str);
	ft_printf("%s\n", *env);
	free(temp);
	temp = NULL;
	if (!(*env))
		return (ft_error("malloc", NO_EXIT));
	return (0);
}

static int	create_env_var(char ***env, char *str)
{
	char	**temp;

	temp = *env;
	*env = init_env(*env, str);
	free_ptr_arr(&temp);
	return (0);
}

static int	change_env_var(char ***env, char *str, int (*f)(char **, char *))
{
	char	*var;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '+')
		++i;
	var = (char *)malloc(i + 1);
	if (!var)
		return (ft_error("malloc", NO_EXIT));
	ft_memmove(var, str, i);
	var[i] = '\0';
	ft_printf("%s\n", var);
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], var, (ft_strlen(var) + 1)) == '=')
			return (free_arr(&var), f(&((*env)[i]), str));
	}
	free_arr(&var);
	create_env_var(env, str);
	return (1);
}

int	ft_export(t_exec *exec, char ***env, t_data *data)
{
	if (exec->n_pipes)
		return (0);
	if (!data || data->token != STRING)
			return (need_sort_env(*env));
	if (ft_strnstr(data->word, "+=", ft_strlen(data->word + 1)))
		return (change_env_var(env, data->word, app_env_var));
	else if (ft_strnstr(data->word, "=", ft_strlen(data->word + 1)))
		return (change_env_var(env, data->word, swap_env_var));
	return (0);
}
