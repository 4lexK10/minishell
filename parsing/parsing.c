/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/07/20 11:49:25 by akiener          ###   ########.fr       */
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

char	*ft_append_word(t_data **data, t_arg arg_env, int *i, char *str)
{
	char	*temp;
	char	*res;

	temp = ft_all_string(data, arg_env, i);
	if (!temp)
		return (free(str), free_list(data), NULL);
	res = new_ft_join(str, temp);
	if (!res)
		return (free_list(data), NULL);
	return (res);
}

static int	ft_just_string(t_data **data, t_arg arg_env, int *i)
{
	char	*str;

	str = NULL;
	str = ft_all_string(data, arg_env, i);
	if (!str)
		return (free_list(data), -1);
	while (arg_env.arg[*i] && ft_isspace(arg_env.arg[*i]) == 0)
	{
		str = ft_append_word(data, arg_env, i, str);
		if (!str)
			return (free_list(data), -1);
	}
	if (addback_stack(data, str) == -1)
		return (free(str), free_list(data), -1);
	free(str);
	return (0);
}

static int	check_line(t_arg arg_env, t_data **data)
{
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	while (arg_env.arg[++i])
	{
		if (ft_isspace(arg_env.arg[i]) == 1);
		else
			if (ft_just_string(data, arg_env, &i) == -1)
				return (-1);
		if (!arg_env.arg[i])
			i--;
	}
	return (0);
}

t_data	*parsing(char *av, char **envp)
{
	t_data	*data;
	t_arg	arg_env;

	data = NULL;
	arg_env.arg = av;
	arg_env.env = envp;
	if (check_line(arg_env, &data) == -1)
		return (NULL);
	
	return (data);
}
