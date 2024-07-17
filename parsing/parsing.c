/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/07/17 16:46:23 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || 
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_string_len(char *av, int i, char end)
{
	int	len;

	len = 0;
	while (av[i] != end)
	{
		if (av[i] == '\0')
			return (len);
		len++;
		i++;
	}
	return (len);
}

static int	check_line(char *av, t_data **data)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '"' || av[i] == '\'')
		{
			if (ft_find_string(data, &i, av, av[i]) == -1)
				return (free_list(data), -1);
		}
		else if (ft_isprint(av[i]) == 1)
		{
			if (ft_isspace(av[i]) == 1);
			else
				if (ft_find_string(data, &i, av, ' ') == -1)
					return (free_list(data), -1);
		}
		i++;
	}
	return (0);
}

t_data	*parsing(char *av)
{
	t_data	*data;

	data = NULL;
	if (check_line(av, &data) == -1)
		return (NULL);
	return (data);
}
