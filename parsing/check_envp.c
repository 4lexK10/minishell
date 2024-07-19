/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:29:00 by akiener           #+#    #+#             */
/*   Updated: 2024/07/19 14:49:54 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_envp(t_data **data, char **envp)
{
	t_data	*link;
	int		i;
	int		y;

	link = *data;
	while (link)
	{
		i = -1;
		while (link->word[++i])
		{
			if (link->word[i] == '$')
				if (ft_change_dollar(&link, envp) == -1)
					return (-1);
		}
	}
}
