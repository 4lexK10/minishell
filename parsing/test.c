/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:00 by akiener           #+#    #+#             */
/*   Updated: 2024/08/14 17:02:19 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int ac, char **av, char **envp)
{
	t_data *data = NULL;
	char *str = "echo caca 2142 \"$TEST\" cat -e << FIN>>test.txt";

	(void)ac;
	(void)av;
	(void)envp;
	data = parsing(str);
	if (!data)
		return (printf("Data = NULL\n"), 1);
	t_data *link = data;
	while (link)
	{
		printf("- %s\n", link->word);
		printf("token -> %d\n", link->token);
		link = link->next;
	}
	// int i = -1;
	// while (test[++i])
	// 	printf("env : %s\n", test[i]);
	// free_list(&data);
	// system("leaks a.out");
	return (0);
}
