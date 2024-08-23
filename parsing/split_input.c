/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:45:30 by akiener           #+#    #+#             */
/*   Updated: 2024/08/23 12:21:45 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	*ft_find_word(int *i, char *arg)
{
	int		y;
	char	*str;

	y = ft_string_len(arg, *i, ' ');
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	str[y] = arg[*i];
	while (arg[++(*i)])
	{
		if (ft_isspace(arg[*i]) == 1 || arg[*i] == '"' || arg[*i] == '\''
			|| ft_is_redir_or_pipe(arg[*i]) == 1)
			break ;
		str[++y] = arg[*i];
	}
	str[++y] = '\0';
	str = check_envp(str);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_find_dbl_quotes(int *i, char *arg, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(arg, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	while (arg[++(*i)] != quote)
	{
		if (arg[*i] == '\0')
			return (free(str), NULL);
		str[y++] = arg[*i];
	}
	str[y] = '\0';
	str = check_envp(str);
	if (!str)
		return (NULL);
	(*i)++;
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

char	*ft_all_string(t_data **data, char *arg, int *i)
{
	char	*str;

	str = NULL;
	if (arg[*i] == '"')
	{
		str = ft_find_dbl_quotes(i, arg, '"');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (arg[*i] == '\'')
	{
		str = ft_find_quotes(i, arg, '\'');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (arg[*i])
	{
		str = ft_find_word(i, arg);
		if (!str)
			return (free_list(data), NULL);
	}
	return (str);
}
