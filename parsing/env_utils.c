/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:21 by akiener           #+#    #+#             */
/*   Updated: 2024/08/27 17:34:30 by akiener          ###   ########.fr       */
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

char	*check_special_env(char *str, int *i)
{
	
}
