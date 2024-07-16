/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:43:17 by akiener           #+#    #+#             */
/*   Updated: 2024/07/16 19:31:39 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(int ac, char **av, char **envp)
{
	if (ac == 1)
		return (0);
	if (ac == 2)
		if (check_one_command(av[1]) == false)
			return (-1);
}
