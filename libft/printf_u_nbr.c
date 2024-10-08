/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:minishell.h
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/09/03 14:53:25 by akiener          ###   ########.fr       */
=======
/*   Created: 2023/11/26 14:45:56 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 07:01:38 by akloster         ###   ########.fr       */
>>>>>>> origin:libft/printf_u_nbr.c
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

<<<<<<< HEAD:minishell.h
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
=======
void	printf_u_nbr(unsigned int args, char *base, int *count)
{
	if (args > 9)
	{
		printf_nbr(args / 10, base, count);
		if (*count == -1)
			return ;
		printf_nbr(args % 10, base, count);
	}
	else
	{
		if (write(2, &base[args], 1) == -1)
		{
			*count = -1;
			return ;
		}
		++(*count);
	}
}
>>>>>>> origin:libft/printf_u_nbr.c
