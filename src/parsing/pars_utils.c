/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:36:20 by akiener           #+#    #+#             */
/*   Updated: 2024/10/06 15:01:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* extern int	g_last_val; */

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_is_redir_or_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static char	*red_to_string(char *arg, int *i)
{
	char	*str;
	int		y;

	str = NULL;
	if (arg[*i + 1] == arg[*i])
		str = malloc(sizeof (char) * 3);
	else
		str = malloc (sizeof (char) * 2);
	if (!str)
		return (NULL);
	y = 0;
	str[y++] = arg[*i];
	if (arg[*i] == arg[*i + 1])
	{
		str[y++] = arg[(*i)++];
		(*i)++;
	}
	str[y] = '\0';
	return (str);
}

int	add_redir_or_pipe(t_data **data, char *arg, int *i)
{
	char	*str;

	str = NULL;
	if (arg[*i] == '>' || arg[*i] == '<')
	{
		str = red_to_string(arg, i);
		if (!str)
			return (-1);
		if (addback_stack(data, str) == -1)
			return (free(str), -1);
		return (free(str), 0);
	}
	str = malloc(sizeof (char) * 2);
	if (!str)
		return (-1);
	str[0] = '|';
	str[1] = '\0';
	if (addback_stack(data, str) == -1)
		return (free(str), -1);
	(*i)++;
	return (free(str), 0);
}

int	for_last_value(char **res, char *str, int *i)
{
	char	*link;
	int		y;
	int		z;
	int		x;

	link = ft_itoa(g_last_val);
	if (!link)
		return (-1);
	*res = malloc(sizeof (char) * (ft_strlen(str) + ft_strlen(link) - 1));
	if (!res[0])
		return (free(link), -1);
	y = -1;
	x = *i;
	while (++y < x)
		res[0][y] = str[y];
	z = -1;
	while (link[++z])
		res[0][y++] = link[z];
	x++;
	while (str[++x])
		res[0][y++] = str[x];
	res[0][y] = '\0';
	*i += z;
	return (free(link), 0);
}
