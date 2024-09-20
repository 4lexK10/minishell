/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/09/20 16:29:17 by akloster         ###   ########.fr       */
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
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# define TOKEN	0
# define WORD	1

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
	int				flag_not_red_pipe;
	int				token;
	struct s_data	*next;
}	t_data;

typedef struct	s_exec
{
	t_data		**data;
	int			**pipes;
	int			n_pipes;
	int			std_in;
	int			std_out;
	int			**pid;
	bool		in_pipe;
}				t_exec;

int		initializer(t_data **arg, char ***env);
int		process_handler(t_exec *exec, char ***env);
t_data	*lexer(char *arg);
int		ft_error(char *str, int need);
void	pipe_handler(t_exec *exec, int i);
int		executioner(t_exec *exec, char ***env, int i);
char	*free_all_path_info(char **str, char ***arr);
void	free_int_arr(int ***arr, int sub_arr_nbr);
void	free_data(t_data **data);
void	free_ptr_arr(char ***s);
int		pipe_cleaner(int **pipes, int n_pipes);
int		needs_preRedir(t_exec *exec, int i_cmd);
int		needs_postRedir(t_exec *exec, int i_cmd);
int		ft_open(char *outfile, int type);
t_data	*skipTo_cmd(t_data *temp, int cmd_i);
int		ft_echo(t_data *data);
int		ft_cd(char ***env, t_data *data);
int		is_built(t_exec *exec, char ***env, int i);
t_data	*find_built(t_data *data);
int		built_handler(t_exec *exec, char ***env, int i);
int		ft_pwd(void);
void	ft_exit(t_exec *exec, char ***env);
int		ft_env(char **env, t_data *data);
int		ft_export(t_exec *exec, char ***env, t_data *data);
char	*init_first(char **env);
char	*get_last(char **env);
char	**init_env(char **envp, char *new_var);
int		need_sort_env(char **env);
void	free_arr(char **ptr);
int		ft_unset(char ***env, t_data *data);
int		swap_env_var(char **env, char *str);
int		change_env_var(char ***env, char *str, int (*f)(char **, char *));

#endif