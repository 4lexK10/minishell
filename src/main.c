/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/30 15:31:26 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	interactive_mode(t_exec *exec, char **envp)
{
	char	*arg;
	t_data	*data;

	init_env(exec, envp);
	if (!(exec->env))
		return (1);
	while (1)
	{
		arg = readline("minish-2.0$ ");
		if (arg && *arg)
			add_history(arg);
		data = lexer(arg);
		if (arg && !data)
			continue ;
		if (!arg) // get signal 
		{
			if (free_exec(exec))
				free_data(&data);
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		my_free(&arg);
		initializer(exec, &data);
	}
	return (0);
}

/* static int	non_interactive_mode(char ***env)
{
	char	*arg;
	t_data	*data;

	arg = readline("minish-2.0$ ");
	if (arg && *arg)
		add_history(arg);
	data = lexer(arg);
	if (arg && !data)
		return (0);
	if (!arg) // get signal 
	{
		free_data(&data);
		free_ptr_arr(env);
		free(env);
		data = NULL;
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (0);
	}
	initializer(&data, env, arg);
	free(arg);
	return (0);
} */

int	main(int ac, char **av, char **envp)
{
	t_exec exec;

	(void)ac;
	(void)av;
	ft_memset(&exec, 0, sizeof(t_exec));
	return (interactive_mode(&exec, envp));
}
