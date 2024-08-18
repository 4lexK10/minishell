/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:19:35 by akloster          #+#    #+#             */
/*   Updated: 2023/11/16 11:41:26 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *s, ...);
void	printf_hex(unsigned int args, char *base, int *count);
void	printf_nbr(int args, char *base, int *count);
void	printf_u_nbr(unsigned int args, char *base, int *count);
void	printf_ptr(unsigned long long args, char *base, int *count);
void	printf_str(char *args, int *count);

#endif