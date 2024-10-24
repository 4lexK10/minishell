/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_our_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:22:11 by akiener           #+#    #+#             */
/*   Updated: 2024/10/24 14:09:36 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	compar_env(char *name, char *env)
{
	int	i;

	i = -1;
	while (name[++i])
		if (name[i] != env[i])
			return (-1);
	if (!env[i] || env[i] != '=')
		return (-1);
	return (0);
}

static int	is_in_env(char *name, char **env, int *i)
{
	while (env[++(*i)])
	{
		// printf("Test = %s\n", env[*i]);
		if (compar_env(name, env[*i]) == 0)
			break ;
	}
	if (!env[*i])
		return (0);
	// printf("Yes : %s !\n", env[*i]);
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
	if (is_in_env(name, env, &i) == 0)
		return (0);
	len = ft_strlen(env[i]) - y - 1;
	*res = malloc(sizeof (char) * (len + 1));
	if (!*res)
		return (0);
	*flag = 1;
	x = -1;
	while (env[i][++y])
		res[0][++x] = env[i][y];
	res[0][++x] = '\0';
	return (1);
}
