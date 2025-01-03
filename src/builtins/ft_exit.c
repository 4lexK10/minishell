/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:43 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 17:05:49 by akloster         ###   ########.fr       */
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

static int	is_zero(t_data *data)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	if (!data || !(data->word))
		return (1);
	str = data->word;
	while (str[++i])
	{
		if (str[i] == '-')
			continue ;
		while (str[i] == '0')
			++i;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

static int	is_num(t_data *data)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	if (!data || !(data->word))
		return (0);
	str = data->word;
	while (str[++i])
	{
		if (str[i] == '-')
			continue ;
		while (ft_isdigit(str[i]))
			++i;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_exit(t_exec *exec, t_data *data)
{
	int	tmp;

	tmp = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (!data || !data->word)
		exit(0);
	tmp = ft_atol(data->word);
	if (is_num(data) && !ft_atol(data->word) && !is_zero(data))
	{
		write(STDERR_FILENO, "minsh: ", 7);
		write(STDERR_FILENO, data->word, ft_strlen(data->word));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		free_exec(exec);
		exit(255);
	}
	free_exec(exec);
	exit(tmp % 256);
}
