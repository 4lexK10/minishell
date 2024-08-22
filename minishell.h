/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/08/22 13:28:39 by akiener          ###   ########.fr       */
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

// token definition

# define PIPE		1
# define IN			2
# define OUT		3
# define OUT_AP		4
# define H_DOC		5
# define STRING		6
# define NUMBER		7
# define BUILT		8
# define ABS_PATH	9

typedef struct	s_data
{
	char			*word;
	int				flag_not_red_pipe;
	int				token;
	struct s_data	*next;
}	t_data;

int		exec(t_data **arg);
int		executor(int n_pipe, t_data **arg);
t_data	**lexer(char *arg);

#endif
