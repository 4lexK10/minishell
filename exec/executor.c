/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:29 by akloster          #+#    #+#             */
/*   Updated: 2024/07/16 20:14:41 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int  piper(t_data **node)
{
	if ((*node)->token == 2) // needs correctiom: pipe token number
	{
		*node = (*node)->next;
		redir_in((*node)->word);
	}
	
}

int executor(int n_pipe, t_data **arg)
{
	t_data *temp;

	temp = *arg;
	while (n_pipe)
	{
		piper(&temp);
	}
}