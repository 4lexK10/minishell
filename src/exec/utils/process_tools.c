/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:24:54 by akloster          #+#    #+#             */
/*   Updated: 2024/10/21 17:45:15 by akloster         ###   ########.fr       */
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

int cmd_exec(t_exec *exec)
{
	int	pid;
	int	status;
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
	{
		waitpid(pid, &status, 0);
		g_last_val = WEXITSTATUS(status);
	}
	return (0);
}
