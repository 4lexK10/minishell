/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/07/09 20:11:35 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_word(char *str)
{
	if (*str == '<' || *str == '>' || *str == '|' || ft_strnstr(str, "<<", 2)
			|| ft_strnstr(str, ">>", 2))
		return (false);
	return (true);
}

t_data	*lexer(char *arg)
{
	int		i;
	char	**args;
	t_data	*head;

	i = -1;
	while (arg[i])
	{
		if (check_word(args[i]))
		{
			
		}	
	}
	return (head);
}
