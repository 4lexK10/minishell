/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:55:06 by akloster          #+#    #+#             */
/*   Updated: 2024/07/17 15:58:00 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data **data)
{
	t_data	*temp;

	if (!data || !(*data))
		return ;
	temp = *data;
	while (temp)
	{
		temp = temp->next;
		(*data)->next = NULL;
		if ((*data)->word)
			free((*data)->word);
		free(*data);
		*data = temp;
	}
}

void free_ptr_array(char ***s)
{
	int	i;

	i = -1;
	if (!s || !(*s))
		return ;
	if (**s)
	{
		while ((*s)[++i])
		{
			free((*s)[i]);
			(*s)[i] = NULL;
		}
	}
	free(*s);
	*s = NULL;
}
