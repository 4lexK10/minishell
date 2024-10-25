/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/10/25 17:04:33 by akiener          ###   ########.fr       */
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

char	*ft_append_word(t_data **data, t_arg line, int *i, char *str)
{
	char	*temp;
	char	*res;

	temp = ft_all_string(data, line, i);
	if (!temp)
		return (free(str), free_list(data), NULL);
	res = new_ft_join(str, temp);
	if (!res)
		return (free_list(data), NULL);
	return (res);
}

static int	ft_just_string(t_data **data, t_arg line, int *i)
{
	char	*str;

	str = NULL;
	str = ft_all_string(data, line, i);
	if (!str)
		return (free_list(data), -1);
	while (line.arg[*i] && ft_isspace(line.arg[*i]) == 0
		&& ft_is_redir_or_pipe(line.arg[*i]) == 0)
	{
		str = ft_append_word(data, line, i, str);
		if (!str)
			return (free_list(data), -1);
	}
	if (addback_stack(data, str) == -1)
		return (free(str), free_list(data), -1);
	last_in_stack(*data)->flag_not_red_pipe = 1;
	free(str);
	return (0);
}

static int	check_line(t_arg line, t_data **data)
{
	int		i;
	int		flag;

	i = -1;
	while (line.arg[++i])
	{
		flag = 0;
		if (ft_isspace(line.arg[i]) == 1)
			;
		else if (ft_is_redir_or_pipe(line.arg[i]) == 1)
		{
			if (add_redir_or_pipe(data, line.arg, &i) == -1)
				return (free_list(data), -1);
			if (ft_isspace(line.arg[i]) == 0)
				flag = 1;
		}
		else
			if (ft_just_string(data, line, &i) == -1)
				return (free_list(data), -1);
		if (!line.arg[i] || ft_is_redir_or_pipe(line.arg[i]) == 1
			|| flag == 1)
			i--;
	}
	return (0);
}

t_data	*parsing(char *av, t_exec *exec)
{
	t_data	*data;
	t_data	*link;
	t_arg	line;

	data = NULL;
	line.arg = av;
	line.env = exec->env;
	if (check_line(line, &data) == -1)
		return (NULL);
	link = data;
	while (link)
	{
		link->token = which_token(link->word, link->flag_not_red_pipe);
		if (!link->next)
			if (change_last_arg(exec, link->word) == -1)
				return (free_data(&data), NULL);
		link = link->next;
	}
	return (data);
}
