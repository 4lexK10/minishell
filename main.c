/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/09 17:32:10 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
