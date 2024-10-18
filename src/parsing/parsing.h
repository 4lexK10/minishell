/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:32:09 by akiener           #+#    #+#             */
/*   Updated: 2024/10/18 17:20:16 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_arg
{
	char	*arg;
	char	**env;
}	t_arg;

t_data	*new_node(char *arg);
t_data	*last_in_stack(t_data *list);
t_data	*parsing(char *av, char **envp);
char	*ft_all_string(t_data **data, t_arg line, int *i);
char	*ft_append_word(t_data **data, t_arg line, int *i, char *str);
char	*new_ft_join(char *str, char *temp);
char	*check_envp(char *str, t_arg line);
char	*check_special_env(char *str, int *i);
void	free_list(t_data **stack);
int		addback_stack(t_data **stack, char *arg);
int		ft_isspace(int c);
int		ft_is_redir_or_pipe(char c);
int		env_name_len(char *word, int i);
int		add_redir_or_pipe(t_data **data, char *arg, int *i);
int		which_token(char *arg, int is_str);
int		compar_comm(char *arg, char *comm);
int		for_last_value(char **res, char *str, int *i);
int		check_our_env(char *name, char **res, char **env, int *flag);

#endif
