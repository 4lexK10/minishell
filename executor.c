/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/07/25 18:22:51 by marvin           ###   ########.fr       */
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

int	ft_fork(int n_pipe);
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error("fork", NO_EXIT);
		return (-1);
	}
	return (pid);
}
// forker ----- needs a check if forks are needed before calling forker()
static int	**forker(int n_pipe)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (int *)malloc((n_pipe + 1) * sizeof(int));
	if (!pids)
		return (NULL);
	while (++i < n_pipe)
		pids[i] = 0;
	i = 0;
	pids[i] = ft_fork(n_pipe);
	while (pids[i] > 0 && ++i >= n_pipe)
		pids[i] = ft_fork();
	if (pid == -1) // error managment for children: all pids before are > 0
		return (&pids);
	return (&pids);
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

int executor(int n_pipe, t_data **data, int ***pipes, char **envp)
{
	t_data	*temp;
	pid_t	**pids;
	int		i;

	i = -1;
	temp = *data;
	if (n_pipe)
	{
		pids = forker(n_pipe);
		if (!pids)
		{
			free_data(data);
			exit(errno);
		}
		while (++i <= n_pipe)
		{
			if ((*pids)[i] == 0)
				run_cmd(data, get_cmd(data, i), envp);
		}
	}
	while (wait(NULL))
		;
	return (0);
}
