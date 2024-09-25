/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:24:27 by akloster          #+#    #+#             */
/*   Updated: 2024/09/26 01:08:20 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (write(STDOUT_FILENO, "=\"", 2) == -1)
				return (1);
		}
		else
			if (write(STDOUT_FILENO, &str[i], 1) == -1)
				return (1);
	}
	if (write(STDOUT_FILENO, "\"\n", 2) == -1)
		return (1);
	return (0);
}

static char	*put_env(char *str)
{
	char *res;

	res = ft_strjoin("declare -x ", str);
	if (!res)
	{
		ft_error("malloc", NO_EXIT);
		return (NULL);
	}
	if (add_quotes(res))
	{
		ft_error("write", NO_EXIT);
		return (NULL);
	}
	free(res);
	res = NULL;
	return (0);
}

char	*init_first(char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = env[0];
	while (env[i])
	{
		if (ft_strncmp(str, env[i], (ft_strlen(str) + 1)) > 0)
			str = env[i];
		++i;
	}
	if (put_env(str))
		return (NULL);
	return (str);
}

char	*get_last(char **env)
{
	char	*last; 
	int		i;

	i = 0;
	last = env[0];
	while (env[++i])
	{
		if (ft_strncmp(last, env[i], (ft_strlen(last) + 1)) < 0)
			last = env[i]; 
	}
	return (last);
}

int	need_sort_env(char **env)
{
	char	*str;
	char	*prev;
	int		i;

	prev = init_first(env);
	if (!prev)
		return (1);
	while (1)
	{
		str = get_last(env);
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(str, env[i], (ft_strlen(str) + 1)) > 0
				&& ft_strncmp(env[i], prev, ft_strlen(env[i])) > 0)
				str = env[i];
			++i;
		}
		if (!ft_strncmp(str, prev, (ft_strlen(str) + 1)))
			break ;
		prev = str;
		if (put_env(str))
			return (ft_error("write", NO_EXIT));
	}
	return (0);
}
