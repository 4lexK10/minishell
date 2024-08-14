/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/08/14 14:34:26 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*new_ft_join(char *str, char *temp)
{
	char	*res;
	int		i;
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

char	*ft_append_word(t_data **data, char *arg, int *i, char *str)
{
	char	*temp;
	char	*res;

	temp = ft_all_string(data, arg, i);
	if (!temp)
		return (free(str), free_list(data), NULL);
	res = new_ft_join(str, temp);
	if (!res)
		return (free_list(data), NULL);
	return (res);
}

static int	ft_just_string(t_data **data, char *arg, int *i)
{
	char	*str;

	str = NULL;
	str = ft_all_string(data, arg, i);
	if (!str)
		return (free_list(data), -1);
	while (arg[*i] && ft_isspace(arg[*i]) == 0
		&& ft_is_redir_or_pipe(arg[*i]) == 0)
	{
		str = ft_append_word(data, arg, i, str);
		if (!str)
			return (free_list(data), -1);
	}
	if (addback_stack(data, str) == -1)
		return (free(str), free_list(data), -1);
	free(str);
	return (0);
}

static int	check_line(char *arg, t_data **data)
{
	int		i;
	int		flag;

	i = -1;
	while (arg[++i])
	{
		flag = 0;
		if (ft_isspace(arg[i]) == 1)
			;
		else if (ft_is_redir_or_pipe(arg[i]) == 1)
		{
			if (add_redir_or_pipe(data, arg, &i) == -1)
				return (free_list(data), -1);
			if (ft_isspace(arg[i]) == 0)
				flag = 1;
		}
		else
			if (ft_just_string(data, arg, &i) == -1)
				return (free_list(data), -1);
		if (!arg[i] || ft_is_redir_or_pipe(arg[i]) == 1
			|| flag == 1)
			i--;
	}
	return (0);
}

t_data	*parsing(char *av)
{
	t_data	*data;
	t_data	*link;

	data = NULL;
	if (check_line(av, &data) == -1)
		return (NULL);
	link = data;
	while (link)
	{
		link->token = which_token(link->word);
		link = link->next;
	}
	return (data);
}
