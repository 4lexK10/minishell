/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:55:50 by akiener           #+#    #+#             */
/*   Updated: 2024/10/04 16:05:04 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Comment faire en sorte que cela check toutes les possibilites ??

int	compar_comm(char *arg, char *comm)
{
	int	len;

	len = (int) ft_strlen(arg);
	if (len != (int) ft_strlen(comm))
		return (-1);
	return (ft_strncmp(arg, comm, len));
}

static int	check_command(char *arg)
{
	int	i;

	if (compar_comm(arg, "echo") == 0 || compar_comm(arg, "cd") == 0
		|| compar_comm(arg, "pwd") == 0 || compar_comm(arg, "export") == 0
		|| compar_comm(arg, "unset") == 0 || compar_comm(arg, "env") == 0
		|| compar_comm(arg, "exit") == 0)
		return (BUILT);
	if (access(arg, F_OK) == 0 && access(arg, X_OK) == 0)
		return (ABS_PATH);
	i = -1;
	while (arg[++i])
		if (ft_isdigit(arg[i]) == 0)
			return (STRING);
	if (!arg[i])
		return (NUMBER);
	return (TOKEN);
}

int	which_token(char *arg, int is_str)
{
	if (ft_is_redir_or_pipe(arg[0]) == 1 && is_str == 0)
	{
		if (arg[0] == '>')
		{
			if (ft_strlen(arg) == 2)
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
