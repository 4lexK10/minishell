/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:47:18 by akloster          #+#    #+#             */
/*   Updated: 2024/08/02 02:34:38 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cmd(t_data **data, int pipe_i)
{
	t_data	*temp;
    char	**cmd;

	temp = *data;
	while (pipe_i-- > 0)
		temp = temp->next->next;
	cmd = ft_split(temp->word, ' ');
    if (!cmd)
		ft_error("malloc", NO_EXIT);
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

/* static void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
} */

int	run_cmd(t_data **data, char **envp, int i)
{
	char	*path;
	char	**cmd;
	/* write(2, "test\n", 5); */
	cmd = get_cmd(data, i);
	if (!cmd)
		return (1);
	path = get_path(cmd, envp);
	if (!path)
		return (1);
	/* put_str_fd(cmd[0]); */
	execve(path, cmd, envp);
	free_data(data);
	free_ptr_arr(&cmd);
	ft_error("execve", NEED_EXIT);
	return (1);
}
