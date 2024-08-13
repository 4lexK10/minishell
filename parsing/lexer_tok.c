/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:55:50 by akiener           #+#    #+#             */
/*   Updated: 2024/08/13 16:17:16 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Comment faire en sorte que cela check toutes les possibilites ??

int	ft_is_command(char *arg)
{
	int	l;
	
	l = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", l) == 0 || ft_strncmp(arg, "cd", l) == 0
		|| ft_strncmp(arg, "pwd", l) == 0 || ft_strncmp(arg, "export", l) == 0
		|| ft_strncmp(arg, "unset", l) == 0 || ft_strncmp(arg, "env", l) == 0
		|| ft_strncmp(arg, "exit", l) == 0)
		return (COMM);
	
}

int	check_command(char *arg)
{
	if (ft_is_command(arg) == 1)
		return (COMM);
}

int	which_token(char *arg)
{
	if (ft_is_redir_or_pipe(arg[0]) == 1)
	{
		if ((arg[0] == '>'))
		{
			if (ft_strlen((arg) == 2))
				return (OUT_AP);
			return (OUT);
		}
		if (arg[0] == '<')
		{
			if (ft_strlen(arg) == 2)
				return (H_DOC);
			return (IN);
		}
		return (PIPE);
	}
	return (check_command(arg));
}
