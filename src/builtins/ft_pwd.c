/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:41:30 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 17:51:10 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_exec *exec)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
		return (ft_error("getcwd", NULL, OG_MSG));
	if (ft_putendl_fd(pathname, STDOUT_FILENO))
		return (ft_error("write", NULL, OG_MSG));
	free(pathname);
	pathname = NULL;
	if (dup2(exec->std_out, STDOUT_FILENO) == -1)
		return (ft_error("dup2", NULL, OG_MSG));
	return (0);
}
