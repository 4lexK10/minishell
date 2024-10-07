/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:03:07 by akloster          #+#    #+#             */
/*   Updated: 2024/10/07 14:45:40 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*skipTo_cmd(t_data *temp, int cmd_i)
{
	/* ft_printf("skipto %d\n", cmd_i); */
	while (cmd_i-- > 0)
	{
		while (temp->token != PIPE)
			temp = temp->next;
		temp = temp->next;
		/* ft_printf("%s\n", temp->next->next->next->word); */
	}
	if (temp->token == IN || temp->token == H_DOC)
		temp = temp->next->next;
/* 	ft_printf("%s\n", temp->word); */
	return (temp);
}

int	cnt_words(t_data *temp)
{
	int		cnt;

	cnt = 0;
	while (temp && temp->word)
	{
		++cnt;
		temp = temp->next;
	}
	return (cnt);
}

void	converter(t_data **data)
{
	t_data *temp;

	temp = *data;
	while (temp)
	{
		if (temp->token >= PIPE && temp->token <= H_DOC)
		{
			free(temp->word);
			temp->word = NULL;
		}
		temp = temp->next;
	}
}