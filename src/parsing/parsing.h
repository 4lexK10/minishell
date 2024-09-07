/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/09/07 20:15:14 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "../../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STRING		6
# define NUMBER		7
# define BUILT		8
# define ABS_PATH	9

typedef struct s_token
{
	bool	command;
	bool	redirection;
	bool	pipe;
	bool	env_var;
	bool	number;
	bool	string;
}	t_token;

typedef struct s_arg
{
	char	*arg;
	pid_t	pid;
}	t_arg;

t_data	*new_node(char *arg);
t_data	*last_in_stack(t_data *list);
int		addback_stack(t_data **stack, char *arg);
void	free_list(t_data **stack);
int		ft_isspace(int c);
int		ft_is_redir_or_pipe(char c);
t_data	*parsing(char *av, pid_t pid);
char	*ft_all_string(t_data **data, t_arg line, int *i);
int		env_name_len(char *word, int i);
char	*check_envp(char *str, pid_t pid);
int		add_redir_or_pipe(t_data **data, char *arg, int *i);
int		which_token(char *arg, int is_str);
int		compar_comm(char *arg, char *comm);
char	*check_special_env(char *str, int *i, pid_t pid);

#endif
