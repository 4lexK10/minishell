/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 07:42:16 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_env(char **envp, char ***env, int n_var)
{
	while (envp[++n_var])
	{
		(*env)[n_var] = ft_strdup(envp[n_var]);
		if (!(*env)[n_var])
		{
			free_ptr_arr(env);
			return (ft_error("malloc", NO_EXIT), NULL);
		}
	}
	(*env)[n_var] = NULL;
	return (*env);
}

char	**init_env(char **envp, char *new_var)
{
	char	**env;
	int		n_var;

	if (!envp || !(*envp))
		return (NULL);
	n_var = 0;
	while (envp[n_var])
		++n_var;
	if (new_var)
		++n_var;
	env = (char **)malloc(sizeof(char *) * (n_var + 1));
	if (!env)
		return (ft_error("malloc", NO_EXIT), NULL);
	n_var = -1;
	if (new_var)
	{
		env[++n_var] = ft_strdup(new_var);
		if (!env[n_var])
		{
			free_ptr_arr(&env);
			return (ft_error("malloc", NO_EXIT), NULL);
		}
	}
	return (fill_env(envp, &env, n_var));
}

int	main(int ac, char **av, char **envp)
{
	char	*arg;
	t_data	*data;
	char	***env;

	(void)ac;
	(void)av;
	env = (char ***)malloc(sizeof(char **));
	if (!env)
		return (ft_error("malloc", NO_EXIT));
	*env = init_env(envp, NULL);
	if (!env)
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
			free_data(&data);
			free_ptr_arr(env);
			free(env);
			data = NULL;
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		initializer(&data, env);
		free_data(&data);
		free(arg);
	}
	return (0);
}
