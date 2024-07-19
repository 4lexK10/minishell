/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/07/19 13:41:13 by akiener          ###   ########.fr       */
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

t_data	*new_node(char *arg);
t_data	*last_in_stack(t_data *list);
int		addback_stack(t_data **stack, char *arg);
void	free_list(t_data **stack);
int		ft_isspace(int c);
t_data	*parsing(char *av);
char	*ft_all_string(t_data **data, char *av, int *i);
char	*ft_append_word(t_data **data, char *av, int *i, char *str);
char	*new_ft_join(char *str, char *temp);

#endif
