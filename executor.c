/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/07/30 22:50:55 by akloster         ###   ########.fr       */
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

static int	ft_fork(void)
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

static int	*forker(int n_fork)
{
	int	*pids;
	int	i;

	i = -1;
	pids = (int *)malloc((n_fork + 1) * sizeof(int)); //     n + 1 for n childs (execs) + 1 parent
	if (!pids)
		return (NULL);
	while (++i <= n_fork)
		pids[i] = 0;
	i = 0;
	pids[i] = ft_fork();
	while (++i <= n_fork)
	{
		if (pids[i - 1] > 0)
			pids[i] = ft_fork();
	}
	if (pids[i] == -1) // error managment for children: all pids before are > 0
		return (pids);
	return (pids);
}

void put_str_fd(char *str) // <<<------- DELETE THIS
{
	while (*str)
	{
		write(2, &(*str), 1);
		++str;
	}
	write(2, "\n", 1);
}

static int	run_cmd(t_data **data, char **cmd, char **envp)
{
	char	*path;

	/* write(2, "test\n", 5); */
	if (!cmd)
		return (1);
	path = get_path(cmd, envp);
	if (!path)
		return (1);
	put_str_fd(path);
	execve(path, cmd, envp);
	free_data(data);
	free_ptr_arr(&cmd);
	ft_error("execve", NEED_EXIT);
	return (1);
}

/* no_pipe_exec(t_data, char **envp)
{
	t_pid	pid;

	pid = ft_fork();
	if (pid == 0)
		run_cmd(data, get_cmd(data, i), envp);
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0)
} */

static int	close_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
	{
		if (close(pipes[i][0]) == -1)
			return (ft_error("close", NO_EXIT));
		if (close(pipes[i][1]) == -1)
			return (ft_error("close", NO_EXIT));
	}
	return (0);
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
		printf("n_pipe = %d\n", n_pipe);
		pids = forker(n_pipe); //GOOD ,but needs error managment for failed fork()
		printf("%d %d %d %d\n", pids[0], pids[1], pids[2], pids[3]);
		if (!pids)
		{
			free_data(data);
			exit(1);
		}
		if (file_handler(pids, pipes, n_pipe)) //PRBLEM
			return (1);
		while (++i <= n_pipe)
		{
			if (pids[i] == 0) // GOOD
				run_cmd(data, get_cmd(data, i), envp);
		}
		if (pids[n_pipe] > 0)
		{
			close_pipes(pipes, n_pipe);
			while (wait(NULL) < 0) // maybe not
				;
		}
	}
	else
		run_cmd(data, get_cmd(data, i), envp);
	return (0);
}
