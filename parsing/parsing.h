/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/09/07 16:47:13 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_arg
{
	char	*arg;
	pid_t	pid;
	int		last_val;
}	t_arg;

t_data	*new_node(char *arg);
t_data	*last_in_stack(t_data *list);
int		addback_stack(t_data **stack, char *arg);
void	free_list(t_data **stack);
int		ft_isspace(int c);
int		ft_is_redir_or_pipe(char c);
t_data	*parsing(char *av, pid_t pid);
char	*ft_all_string(t_data **data, t_arg line, int *i);
char	*ft_append_word(t_data **data, t_arg line, int *i, char *str);
char	*new_ft_join(char *str, char *temp);
int		env_name_len(char *word, int i);
char	*check_envp(char *str, pid_t pid);
int		add_redir_or_pipe(t_data **data, char *arg, int *i);
int		which_token(char *arg, int is_str);
int		compar_comm(char *arg, char *comm);
char	*check_special_env(char *str, int *i, pid_t pid);

#endif
