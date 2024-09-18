/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:23:57 by akloster          #+#    #+#             */
/*   Updated: 2024/09/18 20:39:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data)
{
	if (!data || data->token != STRING)
	{
		if (chdir("") == -1)
			return (ft_error("chdir", NO_EXIT));
		return (0);
	}
	if (data->next && data->next->token == STRING)
	{
		if (write(2, "minish: cd: too many arguments\n", 31) == -1)
			return (ft_error("write", NO_EXIT));
		return (1);
	}
	if (chdir(data->word) == -1)
		return (ft_error("chdir", NO_EXIT));
	return (0);
}
