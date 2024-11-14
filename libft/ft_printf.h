/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:58:40 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 12:17:51 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <stdarg.h>

int		ft_printf(int out, char const *input, ...);
size_t	pt_strlen(const char *str);
int		pt_putstr(int out, char *s);
int		pt_putnbr_fd(int out, int n);
char	*pt_strchr(const char *s, int c);
int		pt_putunsigned(int out, unsigned int n);
int		pt_puthex(int out, char flag, unsigned int num);
int		pt_putptr(int out, void *ptr);

#endif
