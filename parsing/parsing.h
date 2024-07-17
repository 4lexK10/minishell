/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/07/17 16:03:20 by akiener          ###   ########.fr       */
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
t_data	*parsing(char *av);

#endif
