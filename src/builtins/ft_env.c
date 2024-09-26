/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:23:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/26 23:34:07 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *exec, t_data *data)
{
	int	i; 

	i = -1;
	if (data && data->token == 6)
		return (ft_putendl_fd("env: too many arguments", STDOUT_FILENO));
	while ((*(exec->env))[++i])
		ft_putendl_fd((*(exec->env))[i], STDOUT_FILENO);
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NO_EXIT));
	return (0);
}
