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

// Comprendre comment refaire le nouveau mot mais normalement tout devrait etre ok !!

char	*put_env_in_word(t_data **data, int *i)
{

}

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

char	*inside_env(char *word, int i)
{
	char	*env_name;
	char	*env_var;
	int		y;
	int		temp;

	y = env_name_len(word, i);
	// Potentiellement mettre un flag pour si il n'y a rien apres le $ ???
	env_name = malloc(sizeof (char) * (y + 1));
	if (!env_name)
		return (NULL);
	y = -1;
	temp = i + 1;
	while (word[temp] && ft_isspace(word[temp]) == 0 && word[temp] !='$')
	{
		env_name[++y] = word[temp++];
	}
	env_name[++y] = '\0';
	env_var = getenv(env_name);
	free(env_name);
	return (env_var);
}

char	*change_dollar(t_data **data, char **envp, int *i)
{
	int		y;
	char	*res;
	char	*final;

	final = NULL;
	if ((*data)->word[*i + 1] == '?' || (*data)->word[*i + 1] == '$');
		// trouver un moyen de mettre le dernier renvoie d'erreur ou le pid de minishell, puis return (nouvelle structure dans le main ??)
	else
	{
		// Est ce que getenv(char *name) marche ?? a tester 
		res = inside_env((*data)->word, *i); // get_env ne renvoie pas de chaine allouee dynamiquement
		if (!res)
			return (free((*data)->word), (*data)->word = NULL, NULL);
		final = put_env_in_word(data, i);
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
			(*data)->word = change_dollar(data, envp, &i);
			if (!(*data)->word)
				return (free_list(data), -1);
		}
	}
	return (0);
}
