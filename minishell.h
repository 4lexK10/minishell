/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/07/27 17:43:55 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# define TOKEN	0
# define WORD	1

// token definition

# define PIPE	1
# define IN		2
# define OUT	3
# define OUT_AP	4
# define H_DOC	5

// readablitlty defines

# define NO_EXIT	0
# define NEED_EXIT	1
# define FIRST		0
# define LAST		1

typedef struct	s_data
{
	char			*word;
	int				token;
	struct s_data	*next;
}				t_data;

int		exec(t_data **arg, char **envp);
int		executor(int n_pipe, t_data **arg, int **pipes, char **envp);
t_data	*lexer(char *arg);
int		ft_error(char *str, int need);
int		file_handler(int *pids, int **pipes, int n_pipe);
char	*get_path(char **cmd, char **envp);
char	**get_cmd(t_data **data, int pipe_i);
char	*free_all_path_info(char **str, char ***arr);
void	free_int_arr(int ***arr, int sub_arr_nbr);
void	free_data(t_data **data);
void	free_ptr_arr(char ***s);

#endif