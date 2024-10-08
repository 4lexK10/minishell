/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/09/29 23:29:39 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	id_token(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (4);
	if (ft_strnstr(str, "<<", 2))
		return (5);
	if (*str == '<')
		return (2);
	if (*str == '>')
		return (3);
	if (*str == '|') 
		return (1);
	if (ft_strnstr(str, "cd", 3))
		return (8);
	if (ft_strnstr(str, "exit", 5))
		return (8);
	if (ft_strnstr(str, "echo", 5))
		return (8);
	if (ft_strnstr(str, "pwd", 4))
		return (8);
	if (ft_strnstr(str, "env", 4))
		return (8);
	if (ft_strnstr(str, "export", 7))
		return (8);
	if (ft_strnstr(str, "unset", 6))
		return (8);
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
		temp->token = STRING;
	}
	else if (type == TOKEN)
	{
		temp->word = NULL;
		temp->token = id_token(arg);
		if (temp->token == BUILT)
			temp->word = ft_strdup(arg);
		/* ft_printf("lexer:  %d\n", temp->token); */
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
	i = -1;
/* 	for (t_data *test = head; test; test = test->next)
	{
		if (test->token >  0)
			printf("%d: %d\n", ++i, test->token);
		else
			printf("%d: |%s|\n", ++i, test->word);
	} */
	return (head);
}
