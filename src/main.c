/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 17:10:49 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_last_val != -21)
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_val = 1;
	}
	else
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	incr_shlvl(t_exec *exec)
{
	char	*str;
	char	*temp;
	int		nbr;

	str = ft_getenv(exec->env, "SHLVL");
	if (!str)
		return (0);
	nbr = ft_atoi(str);
	temp = ft_itoa(++nbr);
	if (!temp)
	{
		ft_error("malloc", NULL, OG_MSG);
		return (1);
	}
	str = ft_strjoin("SHLVL=", temp);
	my_free(&temp);
	if (!str)
	{
		ft_error("malloc", NULL, OG_MSG);
		return (1);
	}
	if (change_env_var(exec, str, swap_env_var) && my_free(&str))
		return (1);
	my_free(&str);
	return (0);
}

static void	ctrl_d(t_exec *exec, char **arg)
{
	my_free(arg);
	free_exec(exec);
	write(1, "exit\n", 5);
	exit(0);
}

static int	interactive_mode(t_exec *exec, char **envp)
{
	char				*arg;
	t_data				*data;
	struct sigaction	act;

	if (init_env(exec, envp))
		return (1);
	while (1)
	{
		act.sa_handler = &signal_handler;
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGINT, &act, NULL);
		arg = readline("minish-2.0$ ");
		if (!arg)
			ctrl_d(exec, &arg);
		if (arg && *arg)
			add_history(arg);
		data = parsing(arg, exec);
		g_last_val = 0;
		converter(&data, &arg);
		g_last_val = 0;
		if (!data)
			continue ;
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
