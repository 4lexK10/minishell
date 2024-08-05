/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:45:30 by akiener           #+#    #+#             */
/*   Updated: 2024/08/05 12:24:37 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Mieux gerer le cas des doubles quotes avec des mots attaché car ça ne va pas marcher comme ça

static int	ft_string_len(char *av, int i, char end)
{
	int	len;

	len = 0;
	if (av[i] == '"' || av[i] == '\'')
		i++;
	while (av[i] && av[i] != end)
	{
		if (end == ' ' && (ft_isspace(av[i]) == 1 || av[i + 1] == '"'
				|| av[i + 1] == '\''))
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*ft_find_word(int *i, t_arg arg_env)
{
	int		y;
	char	*str;

	y = ft_string_len(arg_env.arg, *i, ' ');
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	str[y] = arg_env.arg[*i];
	while (arg_env.arg[++(*i)])
	{
		if (ft_isspace(arg_env.arg[*i]) == 1 || arg_env.arg[*i] == '"'
			|| arg_env.arg[*i] == '\'')
			break ;
		str[++y] = arg_env.arg[*i];
	}
	str[++y] = '\0';
	str = check_envp(str);
	if (!str)
		return (printf("MAMAMIA\n"), NULL);
	return (str);
}

char	*ft_find_dbl_quotes(int *i, t_arg arg_env, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(arg_env.arg, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	while (arg_env.arg[++(*i)] != quote)
	{
		if (arg_env.arg[*i] == '\0')
			return (free(str), NULL);
		str[y++] = arg_env.arg[*i];
	}
	str[y] = '\0';
	str = check_envp(str);
	if (!str)
		return (printf("MAMAMIA 2\n"), NULL);
	(*i)++;
	return (str);
}

char	*ft_find_quotes(int *i, char *av, char quote)
{
	int		y;
	char	*str;

	y = ft_string_len(av, *i, quote);
	str = malloc(sizeof (char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	while (av[++(*i)] != quote)
	{
		if (av[*i] == '\0')
			return (free(str), NULL);
		str[y++] = av[*i];
	}
	str[y] = '\0';
	(*i)++;
	return (str);
}

char	*ft_all_string(t_data **data, t_arg arg_env, int *i)
{
	char	*str;

	str = NULL;
	if (arg_env.arg[*i] == '"')
	{
		str = ft_find_dbl_quotes(i, arg_env, '"');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (arg_env.arg[*i] == '\'')
	{
		str = ft_find_quotes(i, arg_env.arg, '\'');
		if (!str)
			return (free_list(data), NULL);
	}
	else if (arg_env.arg[*i])
	{
		str = ft_find_word(i, arg_env);
		if (!str)
			return (free_list(data), NULL);
	}
	return (str);
}
