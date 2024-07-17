/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:45:30 by akiener           #+#    #+#             */
/*   Updated: 2024/07/17 17:15:51 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Mieux gerer le cas des doubles quotes avec des mots attaché car ça ne va pas marchercomme ça

static int	ft_string_len(char *av, int i, char end)
{
	int	len;

	len = 0;
	if (av[i] == '"' || av[i] == '\'')
		i++;
	while (av[i] != end)
	{
		if (av[i] == '\0')
			return (len);
		len++;
		i++;
	}
	return (len);
}

char	*ft_join_word(char *str, char *av, int *i, t_data **data)
{
	char	*res;
	int		y;

	while (av[*i])
	{
		if (av[*i] == '"')
			if (ft_find_quotes(data, i, av, '"') == -1)
				return (free(str), NULL);
		if (av[*i] == '\'')
			if (ft_find_quotes(data, i, av, '\'') == -1)
				return (free(str), NULL);
		if (ft_isprint)
			if (ft_find_word())
				return (free(str))
	}
}

int	ft_find_quotes(t_data **data, int *i, char *av, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(av, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (-1);
	y = 0;
	while (av[++(*i)] != quote)
	{
		if (av[*i] == '\0')
			return (free(str), free_list(data), -1);
		str[y++] = av[*i];
	}
	while (ft_isspace(av[++(*i)]) == 0)
	{
		
	}
	str[y] = '\0';
	if (addback_stack(data, str) == -1)
		return (free(str), free_list(data), -1);
	free(str);
	return (0);
}
