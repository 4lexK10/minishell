/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:main.c
/*   Created: 2024/07/04 17:34:23 by akloster          #+#    #+#             */
/*   Updated: 2024/10/01 14:11:58 by akiener          ###   ########.fr       */
=======
/*   Created: 2024/07/09 17:26:54 by akloster          #+#    #+#             */
/*   Updated: 2024/10/08 14:56:13 by akloster         ###   ########.fr       */
>>>>>>> origin:src/builtins/ft_env.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:main.c
int	g_last_val;

static char	**mini_parser(char *arg)
=======
int	ft_env(t_exec *exec, t_data *data)
>>>>>>> origin:src/builtins/ft_env.c
{
	int	i; 

	i = -1;
	if (data && data->token == 6)
		return (ft_putendl_fd("env: too many arguments", STDOUT_FILENO));
	while ((exec->env)[++i])
		ft_putendl_fd((exec->env)[i], STDOUT_FILENO);
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}
