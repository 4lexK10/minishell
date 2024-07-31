/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/07/30 20:42:24 by akloster         ###   ########.fr       */
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
		temp = *head;
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
		temp->word = ft_strdup(arg);
		temp->token = 0;
	}
	if (type == TOKEN)
	{
		temp->word = NULL;
		temp->token = id_token(arg);
	}
	temp->next = NULL;
}

t_data	*lexer(char *arg)
{
	int		i;
	char	**args;
	t_data	*head;

	if (!arg || !(*arg))
		return (NULL);
	i = -1;
	args = ft_split(arg, ' ');	
	if (!args)
		return (NULL);
	head = NULL;
	while (args[++i])
	{
		if (id_token(args[i]))
			init_data(args[i], &head, TOKEN);
		else
			init_data(args[i], &head, WORD);
	}
	free_ptr_arr(&args);
	return (head);
}
