/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/01 14:11:58 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_val;

static char	**mini_parser(char *arg)
{
	char	**args;

	if (ft_strnstr(arg, "echo", ft_strlen(arg)))
	{
		//arg_check();
		if (ft_echo(arg))
			return (NULL);
	}
}

int	main(void)
{
	char	*arg;

	while (1)
	{
		arg = readline("minishel:");
		lexer(arg);
		free(arg);
		arg = NULL;
	}
	return (0);
}
