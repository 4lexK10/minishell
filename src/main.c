/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/12 13:47:23 by akiener          ###   ########.fr       */
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
		if (!arg)
			ft_exit(exec, NULL);
		if (arg && *arg)
			add_history(arg);
		data = parsing(arg, exec->env);
		converter(&data);
		my_free(&arg);
		initializer(exec, &data);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_exec				exec;
	
	(void)ac;
	(void)av;
	g_last_val = 0;
	ft_memset(&exec, 0, sizeof(t_exec));
	return (interactive_mode(&exec, envp));
}
