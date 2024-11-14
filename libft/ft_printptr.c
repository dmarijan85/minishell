/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:08:11 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 12:20:24 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptrlen(unsigned long long value)
{
	int	i;

	i = 0;
	while (value)
	{
		value = value / 16;
		i++;
	}
	return (i);
}

static void	fill(unsigned long long value, char *changed)
{
	int		len;
	char	*hex;

	hex = "0123456789abcdef";
	len = ptrlen(value) + 2;
	changed[len] = '\0';
	len--;
	while (len)
	{
		changed[len] = hex[value % 16];
		len--;
		value = value / 16;
	}
	changed[0] = '0';
	changed[1] = 'x';
}

int	pt_putptr(int out, void *ptr)
{
	unsigned long long	value;
	char				*changed;
	int					ret;

	if (!ptr)
		return (ft_printf(out, "%s", "0x0"));
	value = (unsigned long long)ptr;
	changed = malloc(sizeof(char) * ptrlen(value) + 3);
	if (!changed)
		return (-1);
	fill(value, changed);
	ret = ft_printf(out, "%s", changed);
	free(changed);
	return (ret);
}
