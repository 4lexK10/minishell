/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/07/18 22:25:57 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int  piper(t_data **node)
{
	if ((*node)->token == 2) // needs correctiom: pipe token number
	{
		*node = (*node)->next;
		redir_in((*node)->word);
	}
	
} */

static pid_t	*ft_fork(int n_pipe)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = (pid_t *)malloc(sizeof(pid_t) * n_pipe);
	if (!pids)
	{
		ft_error("malloc", NO_EXIT);
		return (NULL);
	}
	while (++i <= n_pipe)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_error("fork", NO_EXIT);
			free(pids);
			pids = NULL;
			return (NULL);
		}
	}
	return (pids);
}

static int	run_cmd(t_data **data, char **cmd, char **envp)
{
	char	*path;

	if (!cmd)
		return (1);
	path = get_path(cmd, envp);
	if (!path)
		return (1);
	execve(path, cmd, envp);
	free_data(data);
	free_ptr_arr(&cmd);
	ft_error("execve", NEED_EXIT);
	return (1);
}

int executor(int n_pipe, t_data **data, int **pipes, char **envp)
{
	t_data	*temp;
	pid_t	*pids;
	int		i;

	i = -1;
	temp = *data;
	if (n_pipe)
	{
		pids = ft_fork(n_pipe);
		if (!pids)
		{
			free_data(data);
			exit(errno);
		}
		while (++i <= n_pipe)
		{
			if (pids[i] == 0)
			{
				printf("i = %d pipes[0] = %d pipes[1] = %d\n", i, pipes[i][0], pipes[i][1]);
				run_cmd(data, get_cmd(data, i), envp);
			}
		}
	}
	while (wait(NULL))
		;
	return (0);
}
