/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:05:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/16 19:31:20 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_check(t_data **arg)
{
	t_data	*temp;
	int		cnt;

	temp = *arg;
	cnt = 0;
	while (temp)
	{
		if (temp->token == 1) // needs correctiom: pipe token number
			++cnt;
		temp = temp->next;
	}
	return (cnt);
}

int	exec(t_data **arg)
{
	int	n_pipe;
	
	n_pipe = pipe_check(arg);
	executor();
}