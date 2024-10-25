/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:24:08 by akloster          #+#    #+#             */
/*   Updated: 2024/10/25 16:46:01 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	special_case(int need)
{
	if (need == PIPE)
		ft_error("syntax error near unexpected token", "'|'", MY_MSG);
	if (need == IN)
		ft_error("syntax error near unexpected token", "'<'", MY_MSG);
	if (need == OUT)
		ft_error("syntax error near unexpected token", "'>'", MY_MSG);
	if (need == OUT_AP)
		ft_error("syntax error near unexpected token", "'>>'", MY_MSG);
	if (need == H_DOC)
		ft_error("syntax error near unexpected token", "'<<'", MY_MSG);
}

int	ft_error(char *str, char *name, int need)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	if (need >= PIPE && need <= H_DOC)
		special_case(need);
	if (need == MY_MSG)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		if (name)
			ft_putstr_fd(name, STDERR_FILENO);
		return (1);
	}
	if (name)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		perror(name);
	}
	else if (need == OG_MSG)
		perror(str);
	return (1);
}
