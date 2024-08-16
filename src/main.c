/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/08/11 23:06:22 by akloster         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*arg;
	t_data	*data;

	(void)ac;
	(void)av;
	while (1)
	{
		arg = readline("Minish-1.0$ ");
		data = lexer(arg);
		if (!data) // NEEDS fix for ctl + D (has to exit minishell)
			continue ;
/* 		if (!data)
			continue ; */
		exec(&data, envp);
		free_data(&data);
	}
	return (0);
}
