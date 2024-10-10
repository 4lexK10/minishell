/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:34:49 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 18:33:58 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __linux__
#  include <linux/limits.h>

# elif __APPLE__
#  include <limits.h>
# endif

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
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

# define OG_MSG		0
# define MY_MSG		1
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
	char				**env;
	t_data				**data;
	int					**pipes;
	int					n_pipes;
	int					*pid;
	int					std_in;
	int					std_out;
}				t_exec;

int	g_last_val;

t_data *lexer(char *arg); // <=----- DELETE!

void	converter(t_data **data);
int		initializer(t_exec *exec, t_data **data);
int		process_handler(t_exec *exec);
t_data	*parsing(char *av, char **envp);
int		ft_error(char *str, char *name, int need);
void	pipe_handler(t_exec *exec, int i);
int		executioner(t_exec *exec, int i);
char	*free_all_path_info(char **str, char ***arr);
void	free_pipes(t_exec *exec, int max);
void	free_int_arr(int ***arr, int sub_arr_nbr);
void	free_data(t_data **data);
void	free_ptr_arr(char ***s);
int		pipe_cleaner(int **pipes, int n_pipes);
int		needs_preRedir(t_exec *exec, int i_cmd);
int		needs_postRedir(t_exec *exec, int i_cmd);
int		ft_open(char *outfile, int type);
t_data	*skipTo_cmd(t_data *temp, int cmd_i);
int		is_built(t_exec *exec, int i);
t_data	*find_built(t_data *data);
int		built_handler(t_exec *exec, int i);
char	*init_first(char **env);
char	*get_last(char **env);
void	init_env(t_exec *exec, char **envp);
int		need_sort_env(t_exec *exec);
void	my_free(char **ptr);
void	rl_replace_line (const char *text, int clear_undo);
/* void	rl_clear_history (void); */
int		swap_env_var(char **env, char *str);
int		change_env_var(t_exec *exec, char *str, int (*f)(char **, char *));
int		free_exec(t_exec *exec);
int		cnt_words(t_data *temp);
void	pre_exec_free(t_exec *exec);
int		add_quotes(char *str);
void	free_env(t_exec *exec);

int		ft_unset(t_exec *exec, t_data *data);
int		ft_pwd(t_exec *exec);
void	ft_exit(t_exec *exec, t_data *data);
int		ft_env(t_exec *exec, t_data *data);
int		ft_export(t_exec *exec, t_data *data);
int		ft_echo(t_exec *exec, t_data *data);
int		ft_cd(t_exec *exec, t_data *data);

#endif