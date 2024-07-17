/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiener <akiener@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:00 by akiener           #+#    #+#             */
/*   Updated: 2024/07/17 16:15:09 by akiener          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main()
{
	t_data *data = NULL;
	char *str = "Coucou C       est MOI \"Pour voir si      marche   \"yo";

	data = parsing(str);
	if (!data)
		return (printf("Wesh\n"), 1);
	t_data *link = data;
	while (link)
	{
		printf("- %s\n", link->word);
		link = link->next;
	}
	free_list(&data);
	return (0);
}
