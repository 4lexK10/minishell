/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:21:39 by akloster          #+#    #+#             */
/*   Updated: 2024/10/11 17:33:19 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*check_multi(t_data *data)
{
	
}

int	here_doc_handler(t_exec *exec)
{
	t_data *temp;
	int		cmd_i;

	temp = *(exec->data);
	cmd_i = 0;
	while (temp)
	{
		if (temp->token == H_DOC)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (0);
	check_multi();
}