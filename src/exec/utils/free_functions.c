/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:55:06 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:47:48 by akloster         ###   ########.fr       */
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
		{
			free((*data)->word);
			(*data)->word = NULL;
		}
		free(*data);
		*data = temp;
	}
	*data = NULL;
}

void	free_ptr_arr(char ***s)
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

void	free_pipes(t_exec *exec, int max)
{
	int	i;

	i = -1;
	if (!exec->pipes)
		return ;
	while (++i < max)
	{
		free((exec->pipes)[i]);
		(exec->pipes)[i] = NULL;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

char	*free_all_path_info(char **str, char ***arr)
{
	if (!str || !(*str) || !arr || !(*arr) || !(**arr))
		return (NULL);
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	free_ptr_arr(arr);
	return (NULL);
}

int	my_free(char **ptr)
{
	if (!ptr || !(*ptr))
		return (1);
	free(*ptr);
	*ptr = NULL;
	return (1);
}
