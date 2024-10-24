/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/10 13:07:11 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec *exec, t_data *data)
{
	int	i; 

	i = -1;
	if (data && data->token == 6)
		return (ft_putendl_fd("env: too many arguments", STDOUT_FILENO));
	while ((exec->env)[++i])
		ft_putendl_fd((exec->env)[i], STDOUT_FILENO);
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}
