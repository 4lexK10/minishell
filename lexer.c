/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/07/11 00:23:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_token(char *str)
{
	if (*str == '<' || *str == '>' || *str == '|' || ft_strnstr(str, "<<", 2)
			|| ft_strnstr(str, ">>", 2))
		return (true);
	return (false);
}

t_data	*lexer(char *arg)
{
	int		i;
	char	**args;
	t_data	*head;

	i = -1;
	while (arg[i])
	{
		if (check_token(args[i]))
		{
				
		}	
	}
	return (head);
}
