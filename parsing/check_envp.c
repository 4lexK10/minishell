/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:29:00 by akiener           #+#    #+#             */
/*   Updated: 2024/08/23 12:20:05 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*no_env(char *str, int i)
{
	int		y;
	int		len_less;
	char	*res;

	len_less = env_name_len(str, i);
	res = malloc((sizeof (char) * ft_strlen(str)) - (sizeof (char) * len_less));
	if (!res)
		return (free(str), NULL);
	y = -1;
	while (++y < i)
		res[y] = str[y];
	i++;
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '$')
		i++;
	while (str[i])
		res[y++] = str[i++];
	res[y] = '\0';
	free(str);
	printf("test : res = %s\n", res);
	return (res);
}

static char	*put_env_in_word(char *str, int i, char *env_var)
{
	char	*final;
	int		y;
	int		z;

	if (!env_var[0])
		return (no_env(str, i));
	y = ft_strlen(str) + 1;
	final = malloc(sizeof (char) * (ft_strlen(env_var) + y));
	if (!final)
		return (free(str), NULL);
	y = -1;
	while (++y < i)
		final[y] = str[y];
	z = -1;
	while (env_var[++z])
		final[y++] = env_var[z];
	i++;
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '$')
		i++;
	if (!str[i])
		return (free(str), final[y] = '\0', final);
	i--;
	while (str[++i])
		final[y++] = str[i];
	return (final[y] = '\0', free(str), final);
}

static char	*inside_env(char *word, int i)
{
	char	*env_name;
	char	*env_var;
	int		y;
	int		temp;

	y = env_name_len(word, i);
	if (y == 0)
		return ("$");
	env_name = malloc(sizeof (char) * (y + 1));
	if (!env_name)
		return (NULL);
	y = -1;
	temp = i + 1;
	while (word[temp] && ft_isspace(word[temp]) == 0 && word[temp] != '$')
		env_name[++y] = word[temp++];
	env_name[++y] = '\0';
	env_var = getenv(env_name);
	free(env_name);
	if (!env_var)
		env_var = "";
	return (env_var);
}

static char	*change_dollar(char *str, int *i)
{
	char	*res;
	char	*final;

	final = NULL;
	if (str[*i + 1] == '?' || str[*i + 1] == '$')
		;
	else
	{
		res = inside_env(str, *i);
		if (!res)
			return (free(str), NULL);
		str = put_env_in_word(str, *i, res);
		if (!str)
			return (NULL);
		*i += ft_strlen(res);
		res = NULL;
	}
	return (str);
}

char	*check_envp(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			str = change_dollar(str, &i);
			if (!str)
				return (NULL);
			i--;
		}
	}
	return (str);
}
