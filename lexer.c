/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/07/16 20:44:03 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	id_token(char *str)
{
	if (*str == '<')
		return (2);
	else if (*str == '>')
		return (3);
	else if (*str == '|') 
		return (1);
	else if (ft_strnstr(str, "<<", 2))
		return (4);
	else if (ft_strnstr(str, ">>", 2))
		return (5);
	else
		return (0);	
}

static void	init_data(char *arg, t_data **head, int type)
{
	t_data *temp;

	if (!(*head))
	{
		*head = (t_data *)malloc(sizeof(t_data));
		temp = head;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_data *)malloc(sizeof(t_data));
		temp = temp->next;
	}
	if (type == WORD)
	{
		temp->word = arg;
		temp->token = 0;
	}
	if (type == TOKEN)
	{
		temp->word = NULL;
		temp->token = id_token(arg);
	}
}

t_data	**lexer(char *arg)
{
	int		i;
	char	**args;
	t_data	*head;

	i = -1;
	head = NULL;
	while (arg[++i])
	{
		if (id_token(arg[i]))
			init_data(arg[i], &head, TOKEN);
		else
			init_data(arg[i], &head, WORD);
	}
	return (&head);
}
