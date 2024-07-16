/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:50:41 by akiener           #+#    #+#             */
/*   Updated: 2024/07/16 19:11:40 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Je dois aussi check si il y a des fonctions qui sont corrects mais aui ont besoin d'arguments

bool	check_one_command(char *comm)
{
	if (ft_strncmp(comm, "ls", 2) != 0 && ft_strncmp(comm, "pwd", 3) != 0
		&& ft_strncmp(comm, "env", 3) != 0)
		return (ft_error_comm(comm), false);
}
