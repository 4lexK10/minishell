/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:17:40 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:50:25 by akloster         ###   ########.fr       */
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
			return (ft_error("close", NULL, OG_MSG));
		if (close(pipes[i][1]) == -1)
			return (ft_error("close", NULL, OG_MSG));
	}
	return (0);
}

int	ft_open(char *outfile, int type)
{
	int	output;

	if (access(outfile, F_OK) == -1)
		output = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == OUT_AP)
		output = open(outfile, O_APPEND | O_WRONLY);
	else
		output = open(outfile, O_TRUNC | O_WRONLY);
	if (output == -1)
	{
		ft_error("open: ", outfile, OG_MSG);
		return (-1);
	}
	return (output);
}
