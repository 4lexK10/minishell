/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:24:08 by akloster          #+#    #+#             */
/*   Updated: 2024/07/18 15:34:35 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error(char *str, int need)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	if (need == NEED_EXIT)
		exit(errno);
}
