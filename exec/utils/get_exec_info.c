/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:47:18 by akloster          #+#    #+#             */
/*   Updated: 2024/07/18 16:57:25 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd(t_data **data, int pipe_i)
{
	t_data	*temp;
    char    *cmd;
    char    **temp;

	temp = *data;
	while (pipe_i-- > 0)
		temp = temp->next->next;
	temp->word = 
    
    return ();
}


