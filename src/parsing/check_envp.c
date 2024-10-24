/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:29:00 by akiener           #+#    #+#             */
/*   Updated: 2024/10/24 14:56:06 by akloster         ###   ########.fr       */
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
	return (res);
}

static char	*put_env_in_word(char *str, int i, char *env_var)
{
	char	*final;
	int		y;
	int		z;

	if (!env_var[0])
		return (no_env(str, i));
	y = ft_strlen(str) + 1 - env_name_len(str, i);
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
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '$' && str[i] != '\'')
		i++;
	if (!str[i])
		return (free(str), final[y] = '\0', final);
	i--;
	while (str[++i])
		final[y++] = str[i];
	return (final[y] = '\0', free(str), final);
}

static char	*inside_env(char *word, int i, char **env, int *flag)
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
	while (word[temp] && ft_isspace(word[temp]) == 0 && word[temp] != '$'
		&& word[temp] != '\'')
		env_name[++y] = word[temp++];
	env_name[++y] = '\0';
	if (check_our_env(env_name, &env_var, env, flag) == 0)
		env_var = "";
	free(env_name);
	return (env_var);
}

static char	*change_dollar(char *str, int *i, t_arg line)
{
	char	*res;
	int		flag;

	if (str[*i + 1] == '?' || str[*i + 1] == '$' || str[*i + 1] == '0')
		str = check_special_env(str, i);
	else
	{
		flag = 0;
		res = inside_env(str, *i, line.env, &flag);
		if (!res)
			return (free(str), NULL);
		str = put_env_in_word(str, *i, res);
		if (!str)
		{
			if (flag == 1)
				free(res);
			return (NULL);
		}
		*i += ft_strlen(res);
		if (flag == 1)
			free(res);
		res = NULL;
	}
	return (str);
}

char	*check_envp(char *str, t_arg line)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			str = change_dollar(str, &i, line);
			if (!str)
				return (NULL);
			i--;
		}
	}
	return (str);
}
