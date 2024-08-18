/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/08/18 19:38:45 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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

typedef struct	s_data
{
	char			*word;
	int				token;
	struct s_data	*next;
}				t_data;

typedef struct	s_exec
{
	t_data		*data;
	int			**pipes;
	int			n_pipes;
	int			std_in;
	int			std_out
}				t_exec;

typedef struct	s_redir
{
	bool			here_doc;
	char			*stop;
	char			*out;
	char			*in;
	struct s_redir	*next;
}				t_redir;

int		exection(t_data **arg, char **envp);
int		executor(int n_pipes, t_data **arg, int **pipes, char **envp);
t_data	*lexer(char *arg);
int		ft_error(char *str, int need);
void	pipe_handler(int n_pipes, int **pipes, int i);
int		run_cmd(t_data **data, char **envp, int i);
char	*free_all_path_info(char **str, char ***arr);
void	free_int_arr(int ***arr, int sub_arr_nbr);
void	free_data(t_data **data);
void	free_ptr_arr(char ***s);
int		pipe_cleaner(int **pipes, int n_pipes);
int		redir_check(t_data *data, int **pipes, int i_cmd, int n_pipes);
int		pipe_check(t_data **data);



#endif