/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/07/30 02:13:56 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  piper(t_data **node)
{
	if ((*node)->token == 2) // needs correctiom: pipe token number
	{
		*node = (*node)->next;
		redir_in((*node)->word);
	}

}

static pid_t	*ft_frok(t_data **data, int n_pipe)
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
}

static int	run_cmd(t_data **data, char *cmd_name, char **envp)
{
	char	*path;
	char	*arg;

	path = ft_strjoin(get_path(), cmd_name);
	arg = ft_split()
	if (execve(path, arg, envp) == -1)
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
		pids = ft_fork(data, n_pipe);
		if (!pids)
		{
			free_data(data);
			exit(errno);
		}
		while (++i <= n_pipe)
		{
			if (pids[i] == (pid_t ) 0)
				run_cmd(data, get_cmd(data, i), envp);
		}
	}
}
