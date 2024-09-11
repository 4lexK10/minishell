/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:47:18 by akloster          #+#    #+#             */
/*   Updated: 2024/09/07 18:47:20 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cnt_words(t_data *temp)
{
	int		cnt;

	cnt = 0;
	while (temp && temp->word)
	{
		++cnt;
		temp = temp->next;
	}
	return (cnt);
}

static char	**get_cmd(t_data **data, int cmd_i)
{
	t_data	*temp;
    char	**cmd;
	int		cnt;
	int 	i;

	temp = *data;
	cnt = 0;
	i = -1;
	temp = skipTo_cmd(temp, cmd_i);
	cnt = cnt_words(temp);
	cmd = (char **)(malloc)((cnt + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	while (++i < cnt)
	{
		cmd[i] = temp->word;
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

static char	*put_slash(char *cmd)
{
	char	*new_path;

	new_path = ft_strjoin("/", cmd);
	if (!new_path)
		return (NULL);
	return (new_path);
}

static int	*check_cmd(char *cmd, char *cmd_path, char **path, int *i)
{
	char *str;

	*i = 0;
	while (path[++(*i)])
	{
		str = ft_strjoin(path[*i], cmd_path);
		if (access(str, F_OK | X_OK) == 0)
		{
			free(str);
			str = NULL;
			return (i);
		}
	}
	ft_error(cmd, NO_EXIT);
	free(str);
	str = NULL;
	return (NULL);
}

static char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	**path;
	char	*bin;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 6))
		++i;
	path = ft_split(&envp[i][5], ':');
	if (!path)
	{
		ft_error("malloc", NO_EXIT);
		return (NULL);
	}
	bin = put_slash(cmd[0]);
	if (!bin)
	{
		ft_error("malloc", NO_EXIT);
		free_ptr_arr(&path);
		return (NULL);
	}
	if (!check_cmd(cmd[0], bin, path, &i))
		return (free_all_path_info(&bin, &path));
	return (ft_strjoin(path[i], bin));
}


int	executioner(t_exec *exec, int i)
{
	char	*path;
	char	**cmd;

	is_built(exec, i);
	cmd = get_cmd(exec->data, i);
	if (!cmd)
		return (1);
	path = get_path(cmd, exec->envp);
	if (!path)
	{
		free_ptr_arr(&cmd);
		return (1);
	}
/* 	ft_printf("child\n"); */
	execve(path, cmd, exec->envp);
	free_data(exec->data);
	free_ptr_arr(&cmd);
	free(path);
	path = NULL;
	ft_error("execve", NO_EXIT);
	return (1);
}
