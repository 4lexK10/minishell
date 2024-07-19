/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:00 by akiener           #+#    #+#             */
/*   Updated: 2024/07/19 14:36:13 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int ac, char **av, char **envp)
{
	t_data *data = NULL;
	char *str = "t\"ester l'en'\"  vie";

	(void)ac;
	(void)av;
	data = parsing(str);
	if (!data)
		return (printf("Data = NULL\n"), 1);
	t_data *link = data;
	while (link)
	{
		printf("- %s\n", link->word);
		link = link->next;
	}
	int i = -1;
	while (++i == 0)
		printf("env : %s\n", envp[i]);
	free_list(&data);
	system("leaks a.out");
	return (0);
}
