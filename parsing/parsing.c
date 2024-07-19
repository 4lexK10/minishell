/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/07/19 15:13:39 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*new_ft_join(char *str, char *temp)
{
	char	*res;
	int 	i;
	int		y;

	res = malloc(sizeof (char) * (ft_strlen(str) + ft_strlen(temp) + 1));
	if (!res)
		return (free(str), free(temp), NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	y = -1;
	while (temp[++y])
		res[i++] = temp[y];
	res[i] = '\0';
	free(str);
	free(temp);
	return (res);
}

static int	ft_just_string(t_data **data, char *av, int *i)
{
	char	*str;

	str = NULL;
	str = ft_all_string(data, av, i);
	if (!str)
		return (free_list(data), -1);
	while (av[*i] && ft_isspace(av[*i]) == 0)
	{
		str = ft_append_word(data, av, i, str);
		if (!str)
			return (free_list(data), -1);
	}
	if (addback_stack(data, str) == -1)
		return (free(str), free_list(data), -1);
	free(str);
	return (0);
}

static int	check_line(char *av, t_data **data)
{
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	while (av[++i])
	{
		if (ft_isspace(av[i]) == 1);
		else
			if (ft_just_string(data, av, &i) == -1)
				return (-1);
		if (!av[i])
			i--;
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
