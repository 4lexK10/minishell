/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:36:20 by akiener           #+#    #+#             */
/*   Updated: 2024/08/07 16:56:19 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_is_redir_or_pipe(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static char	*red_to_string(char *arg, int *i)
{
	char	*str;
	int		y;

	if (arg[*i + 1] == arg[*i])
		str = malloc(sizeof (char) * 3);
	else
		str = malloc (sizeof (char) * 2);
	if (!str)
		return (NULL);
	y = 0;
	str[y++] = arg[*i];
	if (arg[*i] == arg[*i + 1])
		str[y++] == arg[(*i)++];
	str[y] = '\0';
	return (str);
}

int	add_redir_or_pipe(t_data **data, char *arg, int *i)
{
	char	*str;
	int		y;

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
	return (free(str), 0);
}
