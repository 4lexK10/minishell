/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/07/17 14:55:39 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define TOKEN	0
# define WORD	1

// token definition

# define PIPE	1
# define IN		2
# define OUT	3
# define OUT_AP	4
# define H_DOC	5

typedef struct	s_data
{
	char			*word;
	int				token;
	struct s_data	*next;
}				t_data;

int		exec(t_data **arg);
int		executor(int n_pipe, t_data **arg);
t_data	*lexer(char *arg);
void	free_data(t_data **data);
void	free_ptr_array(char ***s);

#endif