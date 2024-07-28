/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/07/28 02:33:02 by akloster         ###   ########.fr       */
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
		arg = readline("minishel: ");
		data = lexer(arg);
		exec(&data, envp);
		free_data(&data);
	}
	return (0);
}
