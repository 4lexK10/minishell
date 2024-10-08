/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 18:33:26 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	else
	{
		rl_replace_line("", 0);
	    rl_redisplay();
	}
}

static int	interactive_mode(t_exec *exec, char **envp)
{
	char				*arg;
	t_data				*data;
	struct sigaction	act;

	act.sa_handler = &signal_handler;
	init_env(exec, envp);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	if (!(exec->env))
		return (1);
	while (1)
	{
		arg = readline("minish-2.0$ ");
/* 		ft_printf("%d\n", arg[0]); */
		if (!arg)
			ft_exit(exec, NULL);
		if (arg && *arg)
			add_history(arg);
		data = lexer(arg);
/* 		data = parsing(arg, exec->env);
		printf("hello\n");
		converter(&data);
		for (t_data *temp = data; temp; temp = temp->next)
			ft_printf("word->%s token->%d\n", temp->word, temp->token); */
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

/* static void	*signal_handler(int exit_value)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_value);
	return (NULL);
} */

int	main(int ac, char **av, char **envp)
{
	t_exec				exec;
	
	(void)ac;
	(void)av;
	g_last_val = 0;
	ft_memset(&exec, 0, sizeof(t_exec));
	return (interactive_mode(&exec, envp));
}
