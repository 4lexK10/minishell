/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:21 by akiener           #+#    #+#             */
/*   Updated: 2024/09/07 18:15:37 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	env_name_len(char *word, int i)
{
	int	len;
	int	times;

	len = 0;
	times = 0;
	i++;
	while (word[i] && ft_isspace(word[i]) == 0 && word[i] != '$')
	{
		if (word[i] == '\'' && ++times == 2)
			break ;
		len++;
		i++;
	}
	return (len);
}

int	num_len(pid_t pid)
{
	char	*link;
	int		len;

	link = ft_itoa(pid);
	if (!link)
		return (0);
	len = 0;
	while (link[len])
		len++;
	return (free(link), len);
}

char	*put_pid_in_str(char *str, int i, pid_t pid)
{
	char	*res;
	char	*link;
	int		y;
	int		z;

	link = ft_itoa(pid);
	if (!link)
		return (NULL);
	res = malloc(sizeof (char) * (ft_strlen(str) + ft_strlen(link) - 1));
	if (!res)
		return (free(link), NULL);
	y = -1;
	while (++y < i)
		res[y] = str[y];
	z = -1;
	while (link[++z])
		res[y++] = link[z];
	i++;
	while (str[++i])
		res[y++] = str[i];
	res[y] = '\0';
	return (free(link), res);
}

char	*put_str_in_str(char *str, int i, char *put)
{
	char	*final;
	int		y;
	int		z;

	y = ft_strlen(str) + 1 - 2;
	final = malloc(sizeof (char) * (ft_strlen(put) + y));
	if (!final)
		return (NULL);
	y = -1;
	while (++y < i)
		final[y] = str[y];
	z = -1;
	while (put[++z])
		final[y++] = put[z];
	i++;
	while (str[i] && ft_isspace(str[i]) == 0 && str[i] != '$' && str[i] != '\'')
		i++;
	if (!str[i])
		return (final[y] = '\0', final);
	i--;
	while (str[++i])
		final[y++] = str[i];
	return (final[y] = '\0', final);
}

char	*check_special_env(char *str, int *i, pid_t pid)
{
	int 	pid_len;
	char	*res;

	res = NULL;
	if (str[*i + 1] == '$')
	{
		res = put_pid_in_str(str, *i, pid);
		if (!res)
			return (NULL);
		pid_len = num_len(pid);
		if (pid_len == 0)
			return (free(str), NULL);
		*i += pid_len;
	}
	else if (str[*i + 1] == '0')
	{
		res = put_str_in_str(str, *i, "minishell");
		if (!res)
			return (free(str), NULL);
		*i += ft_strlen("minishell");
	}
	else if (str[*i + 1] == '?')
		;
	return (free(str), res);
}
