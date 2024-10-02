/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:43 by akloster          #+#    #+#             */
/*   Updated: 2024/10/02 02:34:54 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_exec(t_exec *exec)
{
	if (!exec)
		return (1);
	free_data(exec->data);
	if (exec->n_pipes > 0)
	{
		free_pipes(exec, exec->n_pipes);
		free(exec->pid);
		exec->pid = NULL;
	}
	free_env(exec);
	return (0);
}

static int	check_word(t_data *data)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	ft_printf("test%s\n", str);
	if (!data || !(data->word))
		return (0);
	str = data->word;
	while (str[++i])
	{
		if (str[i] == '-')
			continue ;
		while (str[i] == '0')
			++i;
	}
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	ft_exit(t_exec *exec, t_data *data)
{
	int	tmp;
	
	tmp = 0;
	if (data && data->word)
		tmp = ft_atol(data->word);
	dup2(exec->std_out, STDOUT_FILENO);
	free_exec(exec);
	/* rl_clear_history(); */
	write(STDOUT_FILENO, "exit\n", 5);
	if (check_word(data))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		write(STDOUT_FILENO, "minsh: ", 7);
		write(STDOUT_FILENO, data->word, ft_strlen(data->word));
		write(STDOUT_FILENO, ": numeric argument required\n", 28);
		tmp = 255;
	}
	exit(tmp % 256);
}
