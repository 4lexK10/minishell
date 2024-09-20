/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:23:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/20 17:10:02 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(char ***env, char *new_pwd)
{
	char	*old_pwd;
	char	*str;

	old_pwd = getenv("PWD");
	str = ft_strjoin("OLD_PWD=", old_pwd);
	if (!str)
		return (ft_error("malloc", NO_EXIT));
	if (change_env_var(env, str, swap_env_var))
		return (free_arr(&str), 1);
	free(str);
	str = ft_strjoin("PWD=", new_pwd);
	if (!str)
		return (ft_error("malloc", NO_EXIT));
	if (change_env_var(env, str, swap_env_var))
		return (free_arr(&str), 1);
	return (0);
}

static int incomplete_dir(char ***env, char *str) // incomplete NOTfinished
{
	char	*dir;

	dir = getenv("HOME");
	if (!ft_strncmp(str, "~", 2) || !ft_strncmp(str, "~/", 3))
	{
		if (chdir(dir) == -1)
			return (ft_error("cd", NO_EXIT));
		update_env(env, dir);
	}
	dir = ft_strjoin(dir, ++str);
	if (!dir)
		return (ft_error("malloc", NO_EXIT));
	return (0);
}

int	ft_cd(char ***env, t_data *data)
{
	if (ft_strlen(data->word) > PATH_MAX)
		return (ft_error("cd", NO_EXIT));
	if (!data || data->token != STRING || !ft_strncmp(data->word, "~", 1))
	{
		if (incomplete_dir(env, data->word))
			return (1);
	}
	if (data->next && data->next->token == STRING)
	{
		if (write(2, "minish: cd: too many arguments\n", 31) == -1)
			return (ft_error("write", NO_EXIT));
		return (1);
	}
	if (chdir(data->word) == -1)
		return (ft_error("cd", NO_EXIT));
	update_env(env, data->word);
	return (0);
}
