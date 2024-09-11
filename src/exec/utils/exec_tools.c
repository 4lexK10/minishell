/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:03:07 by akloster          #+#    #+#             */
/*   Updated: 2024/09/11 02:32:15 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*skipTo_cmd(t_data *temp, int cmd_i)
{
	/* ft_printf("skipto %d\n", cmd_i); */
	while (cmd_i-- > 0)
	{
		while (temp->token != PIPE)
			temp = temp->next;
		temp = temp->next;
		/* ft_printf("%s\n", temp->next->next->next->word); */
	}
	if (temp->token == IN || temp->token == H_DOC)
		temp = temp->next->next;
/* 	ft_printf("%s\n", temp->word); */
	return (temp);
}

void	is_built(t_exec *exec, int i)
{
	t_data	*temp;
	int		res;

	temp = skipTo_cmd(*(exec->data), i);
	ft_printf("%s\n", (*(exec->data))->word);
	if (temp->token != 8)
		return ;
	res = ft_cd(temp->next, exec->in_pipe);
	free_data(exec->data);
	if (exec->in_pipe)
		free(exec->pid);
	free_int_arr(&(exec->pipes), exec->n_pipes);
	exit(res);
}