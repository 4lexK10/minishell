/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:24:27 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:45:42 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_env(char *str)
{
	char	*res;

	res = ft_strjoin("declare -x ", str);
	if (!res)
	{
		ft_error("malloc", NULL, OG_MSG);
		return (NULL);
	}
	if (add_quotes(res))
	{
		ft_error("write", NULL, OG_MSG);
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

static int	put_all_env(t_exec *exec, char *prev)
{
	char	*str;
	char	**env;
	int		i;

	env = exec->env;
	while (1)
	{
		str = get_last(env);
		i = -1;
		while ((env[++i]))
		{
			if (ft_strncmp(str, env[i], (ft_strlen(str) + 1)) > 0
				&& ft_strncmp(env[i], prev, (ft_strlen(env[i]) + 1)) > 0)
				str = env[i];
		}
		if (!ft_strncmp(str, prev, (ft_strlen(str) + 1)))
			break ;
		prev = str;
		if (put_env(str))
			return (ft_error("write", NULL, OG_MSG));
	}
	return (0);
}

int	need_sort_env(t_exec *exec)
{
	char	*prev;

	prev = init_first(exec->env);
	if (!prev)
		return (1);
	if (put_all_env(exec, prev))
		return (1);
	return (0);
}
