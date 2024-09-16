/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:23:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/16 20:26:50 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *exec, t_data *data)
{
	int	i; 

	i = -1;
	if (data && data->token == 6)
		return (ft_putendl_fd("env: too many arguments", STDOUT_FILENO));
	while (exec->env[++i])
		ft_putendl_fd(exec->env[i], STDOUT_FILENO);
	return (0);
}
