/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:24:54 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:27:55 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int built_exec(t_exec *exec)
{
	int ret_pre;
	int ret_post;

	ret_pre = needs_pre_redir(exec, 0);
	ret_post = needs_post_redir(exec, 0);
	if (ret_pre == 1 || ret_post == 1)
		return (1);
	is_cmd_valid(exec, 0);
	executioner(exec, 0);
	return (0);
}

/* static void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		
		g_last_val = 130;
	}
} */

static void parent_handler(int pid)
{
	int	status;
	
	g_last_val = -21;
	waitpid(pid, &status, 0);
	if (status == 2)
		g_last_val = 130;
	else
		g_last_val = WEXITSTATUS(status);
}

int cmd_exec(t_exec *exec)
{
	int	pid;
	int	ret_pre;
	int	ret_post;

	ret_pre = 0;
	ret_post = 0;
	pid = fork();
	if (pid == -1)
		return (ft_error("fork", NULL, OG_MSG));
	else if (pid == 0)
	{   
		ret_pre = needs_pre_redir(exec, 0);
		ret_post = needs_post_redir(exec, 0);
		if (ret_pre == 1 || ret_post == 1)
			exit(1);
		is_cmd_valid(exec, 0);
		executioner(exec, 0);
	}
	else
		parent_handler(pid);
	return (0);
}
