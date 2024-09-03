/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:21 by akiener           #+#    #+#             */
/*   Updated: 2024/09/03 16:15:47 by akiener          ###   ########.fr       */
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

char	*put_pid_in_str(char *str, int *i, pid_t pid)
{
	char	*res;
	char	*link;
	int		y;
	int		len_pid;

	
}

char	*check_special_env(char *str, int *i, pid_t pid)
{
	char	*res;

	if (str[*i + 1] == '$')
		res = put_pid_in_str(str, i, pid);
}
