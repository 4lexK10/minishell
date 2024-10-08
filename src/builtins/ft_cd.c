/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:23:57 by akloster          #+#    #+#             */
/*   Updated: 2024/10/08 17:20:05 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *var)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (env[++i] && ft_strncmp(env[i], var, (ft_strlen(var) + 1)) != '=')
		;
	if (env[i])
	{
		while (env[i][++j] != '=')
			;
		return (&env[i][++j]);
	}
	return (env[i]);
}

static int	update_env(t_exec *exec)
{
	char	*old_pwd;
	char	*str;
	char	*new_pwd;

	old_pwd = ft_getenv(exec->env, "PWD");
	str = ft_strjoin("OLDPWD=", old_pwd);
	if (!str)
		return (ft_error("malloc", NULL, OG_MSG));
	if (change_env_var(exec, str, swap_env_var))
		return (my_free(&str), 1);
	my_free(&str);
	new_pwd = ft_calloc(PATH_MAX, sizeof(char));
	if (!new_pwd)
		return (ft_error("malloc", NULL, OG_MSG));
	new_pwd = getcwd(new_pwd, PATH_MAX);
	if (!new_pwd)
		return (ft_error("getcwd", NULL, OG_MSG));
	str = ft_strjoin("PWD=", new_pwd);
	my_free(&new_pwd);
	if (!str)
		return (ft_error("malloc", NULL, OG_MSG));
	if (change_env_var(exec, str, swap_env_var))
		return (my_free(&str), 1);
	my_free(&str);
	return (0);
}

static int	incomplete_dir(t_exec *exec, t_data *data)
{
	char	*dir;
	
	dir = getenv("HOME");
	if (!data || !data->word || !ft_strncmp(data->word, "~", 2)
		|| !ft_strncmp(data->word, "~/", 3))
	{
		if (chdir(dir) == -1)
			return (ft_error("cd: ", data->word, OG_MSG));
		update_env(exec);
	}
	else if (!ft_strncmp(data->word, "~/", 2))
	{
		dir = ft_strjoin(dir, ++(data->word));
		if (!dir)
			return (ft_error("malloc", NULL, OG_MSG));
		if (chdir(dir) == -1)
			return (my_free(&dir), ft_error("cd: ", dir, OG_MSG));
		my_free(&dir);
	}
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}

int	ft_cd(t_exec *exec, t_data *data)
{
	if (!data || (data->token != STRING && data->token != ABS_PATH)
		|| !ft_strncmp(data->word, "~/", 2)
		|| !ft_strncmp(data->word, "~", 2))
		return (incomplete_dir(exec, data));
	if (ft_strlen(data->word) > PATH_MAX)
		return (ft_error("cd: ", data->word, OG_MSG));
	if (!ft_strncmp(data->word, ".", 2))
		return (0);
	if (data->next && (data->next->token == STRING || data->next->token == ABS_PATH))
		return (ft_error("cd: too many arguments\n", NULL, MY_MSG));
	if (chdir(data->word) == -1)
		return (ft_error("cd: ", data->word, OG_MSG));
	update_env(exec);
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}
