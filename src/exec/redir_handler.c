/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:48:19 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 12:47:20 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int needs_preRedir(t_data *data)
{
 	while (data && data->token != IN && data->token != PIPE)
	{
		data = data->next;
	}
	if (!data || data->token == PIPE)
		return (1);
	if ()
}

static int	needs_postRedir(t_data *data, int i)
{
	while (data->token != )
	{
		/* code */
	}
}

int	redir_check(t_data *data, int i_cmd)
{
	int		n_pipes;

	n_pipes = pipe_check(data);
	while (--i_cmd > 0)
	{
		while (data->token != PIPE)
		{
			data = data->next
		}
		if (needs_preRedir(data))
			
	}
}


