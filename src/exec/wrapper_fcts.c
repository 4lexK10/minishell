/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:17:40 by akloster          #+#    #+#             */
/*   Updated: 2024/08/21 06:50:37 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_cleaner(int **pipes, int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
	{
		if (close(pipes[i][0]) == -1)
			return (ft_error("close", NO_EXIT));
		if (close(pipes[i][1]) == -1)
			return (ft_error("close", NO_EXIT));
	}
	return (0);
}



