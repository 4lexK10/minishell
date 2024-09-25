/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:23:23 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 02:22:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env, t_data *data)
{
	int	i; 

	i = -1;
	if (data && data->token == 6)
		return (ft_putendl_fd("env: too many arguments", STDOUT_FILENO));
	while (env[++i])
		ft_putendl_fd(env[i], STDOUT_FILENO);
	return (0);
}
