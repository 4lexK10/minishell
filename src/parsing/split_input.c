/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:45:30 by akiener           #+#    #+#             */
/*   Updated: 2024/10/16 17:53:01 by akloster         ###   ########.fr       */
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

char	*ft_find_word(int *i, t_arg line)
{
	int		y;
	char	*str;

	y = ft_string_len(line.arg, *i, ' ');
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	str[y] = line.arg[*i];
	while (line.arg[++(*i)])
	{
		if (ft_isspace(line.arg[*i]) == 1 || line.arg[*i] == '"'
			|| line.arg[*i] == '\'' || ft_is_redir_or_pipe(line.arg[*i]) == 1)
			break ;
		str[++y] = line.arg[*i];
	}
	str[++y] = '\0';
	if (compar_comm(str, "$") == 0 && (line.arg[*i] == '"'
			|| line.arg[*i] == '\''))
		return (ft_strdup(""));
	str = check_envp(str, line);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_find_dbl_quotes(int *i, t_arg line, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(line.arg, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	while (line.arg[++(*i)] != quote)
	{
		if (line.arg[*i] == '\0')
			return (free(str), NULL);
		str[y++] = line.arg[*i];
	}
	str[y] = '\0';
	str = check_envp(str, line);
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

char	*ft_all_string(t_data **data, t_arg line, int *i)
{
	char	*str;

	str = NULL;
	if (line.arg[*i] == '"')
	{
		str = ft_find_dbl_quotes(i, line, '"');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (line.arg[*i] == '\'')
	{
		str = ft_find_quotes(i, line.arg, '\'');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (line.arg[*i])
	{
		str = ft_find_word(i, line);
		if (!str)
			return (free_list(data), NULL);
	}
	return (str);
}
