/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/07/20 11:50:57 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_token
{
	bool	command;
	bool	redirection;
	bool	pipe;
	bool	env_var;
	bool	number;
	bool	string;
}	t_token;

typedef struct s_arg
{
	char	*arg;
	char	**env;
}	t_arg;

t_data	*new_node(char *arg);
t_data	*last_in_stack(t_data *list);
int		addback_stack(t_data **stack, char *arg);
void	free_list(t_data **stack);
int		ft_isspace(int c);
t_data	*parsing(char *av, char **envp);
char	*ft_all_string(t_data **data, t_arg arg_env, int *i);
char	*ft_append_word(t_data **data, t_arg arg_env, int *i, char *str);
char	*new_ft_join(char *str, char *temp);

#endif
