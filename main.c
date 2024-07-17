/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/17 17:46:39 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	**mini_parser(char *arg)
{
	char	**args;

	if (ft_strnstr(arg, "echo", ft_strlen(arg)))
	{
		//arg_check();
		if (ft_echo(arg))
			return (NULL);
	}
} */

int	main(void)
{
	char	*arg;
	t_data	*data;

	while (1)
	{
		arg = readline("minishel:");
		data = lexer(arg);
		if (!exec(data))
			return (1);
		free_data(&data);
	}
	return (0);
}
