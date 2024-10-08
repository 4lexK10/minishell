/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:52:56 by akloster          #+#    #+#             */
/*   Updated: 2024/09/14 19:24:58 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	unsigned char const	*p1;
	unsigned char const	*p2;
	size_t				i;

	if (!s1 || !s2)
		return (-1);
	p1 = (unsigned char const *)s1;
	p2 = (unsigned char const *)s2;
	i = 0;
	while (p1[i] == p2[i] && p1[i] != '\0' && p2[i] != '\0' && i < n - 1)
		++i;
	if (n == 0)
		return (0);
	return (p1[i] - p2[i]);
}

/* #include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = "test\0";
	char str2[] = "testa\200";
	size_t lim = 5;
	printf("   strncmp = %d\nft_strncmp = %d\n", strncmp(str1, str2, lim), 
	ft_strncmp(str1, str2, lim));
} */