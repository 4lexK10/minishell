/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:41:30 by akloster          #+#    #+#             */
/*   Updated: 2024/09/16 01:42:36 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_data *data)
{
	char	*pathname;

	if (data && data->token == STRING)
		return (0);
	pathname = getcwd(NULL, 0);
	if (!pathname)
		return (ft_error("getcwd", NO_EXIT));
	if (ft_putendl_fd(pathname, STDOUT_FILENO))
		return (ft_error("write", NO_EXIT));
	free(pathname);
	pathname = NULL;
	return (0);
}
