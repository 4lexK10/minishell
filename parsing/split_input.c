/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:45:30 by akiener           #+#    #+#             */
/*   Updated: 2024/07/19 14:35:49 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Mieux gerer le cas des doubles quotes avec des mots attaché car ça ne va pas marcher comme ça

static int	ft_string_len(char *av, int i, char end)
{
	int	len;

	len = 0;
	if (av[i] == '"' || av[i] == '\'')
		i++;
	while (av[i] && av[i] != end)
	{
		if (end == ' ' && (ft_isspace(av[i]) == 1 || av[i + 1] == '"'
				|| av[i + 1] == '\''))
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*ft_append_word(t_data **data, char *av, int *i, char *str)
{
	char	*temp;
	char	*res;

	temp = ft_all_string(data, av, i);
	if (!temp)
		return (free(str), free_list(data), NULL);
	res = new_ft_join(str, temp);
	if (!res)
		return (free_list(data), NULL);
	// if (!av[*i + 1])
	// 	(*i)++;
	return (res);
}

char	*ft_find_word(int *i, char *av)
{
	int		y;
	char	*str;

	y = ft_string_len(av, *i, ' ');
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	str[y] = av[*i];
	while (av[++(*i)])
	{
		if (ft_isspace(av[*i]) == 1 || av[*i] == '"' || av[*i] == '\'')
			break ;
		str[++y] = av[*i];
	}
	str[++y] = '\0';
	printf("str = %s\n", str);
	// if (!av[*i])
	// 	(*i)--;
	return (str);
}

char	*ft_find_quotes(int *i, char *av, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(av, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	while (av[++(*i)] != quote)
	{
		if (av[*i] == '\0')
			return (free(str), NULL);
		str[y++] = av[*i];
	}
	str[y] = '\0';
	(*i)++;
	return (str);
}

char	*ft_all_string(t_data **data, char *av, int *i)
{
	char	*str;

	str = NULL;
	if (av[*i] == '"')
	{
		str = ft_find_quotes(i, av, '"');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (av[*i] == '\'')
	{
		str = ft_find_quotes(i, av, '\'');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (av[*i])
	{
		str = ft_find_word(i, av);
		if (!str)
			return (free_list(data), NULL);
	}
	return (str);
}
