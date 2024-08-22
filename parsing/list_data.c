/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:01:19 by akiener           #+#    #+#             */
/*   Updated: 2024/08/22 13:28:48 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*new_node(char *arg)
{
	t_data	*n_node;

	n_node = malloc (sizeof (t_data));
	if (!n_node)
		return (NULL);
	n_node->word = ft_strdup(arg);
	if (!n_node->word)
		return (NULL);
	n_node->next = NULL;
	n_node->flag_not_red_pipe = 0;
	return (n_node);
}

t_data	*last_in_stack(t_data *list)
{
	t_data	*link;

	if (!list)
		return (NULL);
	while (list)
	{
		link = list;
		list = list->next;
	}
	return (link);
}

int	addback_stack(t_data **stack, char *arg)
{
	t_data	*new;

	new = new_node(arg);
	if (!new)
		return (-1);
	if (!stack || !*stack)
	{
		*stack = new;
		return (0);
	}
	last_in_stack(*stack)->next = new;
	return (0);
}

void	free_list(t_data **stack)
{
	t_data	*temp;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp->word);
		free(temp);
	}
	return ;
}
