/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/08/21 21:39:16 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# define TOKEN	0
# define WORD	1

// token definition

# define PIPE		1
# define IN			2
# define OUT		3
# define OUT_ADD	4
# define H_DOC		5

// readablitlty defines

# define NO_EXIT	0
# define NEED_EXIT	1
# define FIRST		0
# define LAST		1
# define SINGLE		0
# define DOUBLE		1
# define FOUND		0
# define FAILED		1

typedef struct	s_data
{
	char			*word;
	int				token;
	struct s_data	*next;
}				t_data;

typedef struct	s_exec
{
	t_data		**data;
	char		**envp;
	int			**pipes;
	int			n_pipes;
	int			std_in;
	int			std_out;
}				t_exec;

int		execution(t_data **arg, char **envp);
int		executor(t_exec *exec);
t_data	*lexer(char *arg);
int		ft_error(char *str, int need);
void	pipe_handler(t_exec *exec, int i);
int		run_cmd(t_data **data, char **envp, int i);
char	*free_all_path_info(char **str, char ***arr);
void	free_int_arr(int ***arr, int sub_arr_nbr);
void	free_data(t_data **data);
void	free_ptr_arr(char ***s);
int		pipe_cleaner(int **pipes, int n_pipes);
int		pipe_check(t_data **data);
int		needs_preRedir(t_exec *exec, int i_cmd);
int		needs_postRedir(t_exec *exec, int i_cmd);


#endif