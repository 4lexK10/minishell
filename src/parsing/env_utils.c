/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:21 by akiener           #+#    #+#             */
/*   Updated: 2024/10/24 13:22:46 by akiener          ###   ########.fr       */
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
	i += 2;
	if (!str[i])
		return (final[y] = '\0', final);
	i--;
	while (str[++i])
		final[y++] = str[i];
	return (final[y] = '\0', final);
}

char	*check_special_env(char *str, int *i)
{
	char	*res;

	res = NULL;
	if (str[*i + 1] == '0')
	{
		res = put_str_in_str(str, *i, "minish");
		if (!res)
			return (free(str), NULL);
		*i += ft_strlen("minish");
	}
	else if (str[*i + 1] == '?')
		if (for_last_value(&res, str, i) == -1)
			return (free(str), NULL);
	return (free(str), res);
}
