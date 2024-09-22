/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_our_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:22:11 by akiener           #+#    #+#             */
/*   Updated: 2024/09/22 18:30:12 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_in_env(char *name, char **env, int len_name, int *i)
{
	while (env[++(*i)])
	{
		if (ft_strnstr(env[*i], name, len_name))
			break ;
	}
	if (!env[*i])
		return (0);
	return (1);
}

int	check_our_env(char *name, char **res, char **env, int *flag)
{
	int	len;
	int	i;
	int	y;
	int	x;

	y = ft_strlen(name);
	i = -1;
	if (is_in_env(name, env, y, &i) == 0)
		return (0);
	len = ft_strlen(env[i]) - y - 1;
	printf("len_name = %d\n", y);
	*res = malloc(sizeof (char) * (len + 1));
	if (!*res)
		return (0);
	printf("len_var = %d\n", len);
	x = -1;
	while (env[i][++y])
	{
		printf("yo : %c\n", env[i][y]);
		res[0][++x] = env[i][y];
	}
	res[0][++x] = '\0';
	return (*flag = 1, 1);
}
