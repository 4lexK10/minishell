/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:29:00 by akiener           #+#    #+#             */
/*   Updated: 2024/07/20 13:15:14 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*change_dollar(char *word, char **envp, int *i)
{
	int		i;
	int		y;
	char	*res;

	if (word[*i + 1] == '?' || word[*i + 1] == '$');
		// trouver un moyen de mettre le dernier renvoie d'erreur ou le pid de minishell, puis return (nouvelle structure dans le main ??)
	else
	{
		// Est ce que getenv(char *name) marche ?? a tester 
		
	}
}

int	check_envp(t_data **data, char **envp)
{
	int		i;

	i = -1;
	while ((*data)->word[++i])
	{
		if ((*data)->word[i] == '$')
		{
			(*data)->word = change_dollar((*data)->word, envp, &i);
			if (!(*data)->word)
				return (free_list(data), -1);
		}
	}
	return (0);
}
