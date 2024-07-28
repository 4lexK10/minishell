/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:21 by akiener           #+#    #+#             */
/*   Updated: 2024/07/28 15:10:36 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	env_name_len(char *word, int i)
{
	int	len;

	len = 0;
	i++;
	while (word[i] && ft_isspace(word[i]) == 0 && word[i] != '$')
	{
		len++;
		i++;
	}
	return (len);
}
