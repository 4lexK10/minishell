/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:04:41 by akloster         ###   ########.fr       */
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

void	incr_shlvl(t_exec *exec)
{
	char	*str;
	char	*temp;
	int		nbr;

	str = ft_getenv(exec->env, "SHLVL");
	if (!str)
		return ;
	nbr = ft_atoi(str);
	temp = ft_itoa(++nbr);
	if (!temp)
	{
		ft_error("malloc", NULL, OG_MSG);
		exit(1);
	}
	str = ft_strjoin("SHLVL=", temp);
	my_free(&temp);
	if (!str)
	{
		ft_error("malloc", NULL, OG_MSG);
		exit(1);
	}
	if (change_env_var(exec, str, swap_env_var) && my_free(&str))
		exit(1);
	my_free(&str);
}

static void	ctrl_D(t_exec *exec, char **arg)
{
	my_free(arg);
	free_exec(exec);
/* 	rl_replace_line("", 0);
	rl_redisplay(); */
	write(1, "exit\n", 5);
	exit(0);
}

static int	interactive_mode(t_exec *exec, char **envp)
{
	char				*arg;
	t_data				*data;
	struct sigaction	act;

	init_env(exec, envp);
	if (!(exec->env))
		return (1);
	while (1)
	{
		act.sa_handler = &signal_handler;
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGINT, &act, NULL);
		arg = readline("minish-2.0$ ");
		if (!arg)
			ctrl_D(exec, &arg);
		if (arg && *arg)
			add_history(arg);
		data = parsing(arg, exec->env);
		converter(&data);
		if (!data)
			continue ;
		my_free(&arg);
		initializer(exec, &data, &act);
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
