/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:19:41 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 12:21:24 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	digit_counter(unsigned int n)
{
	unsigned int	i;
	unsigned int	copy;

	i = 0;
	if (n == 0)
		return (1);
	copy = n;
	while (copy > 0)
	{
		copy = copy / 10;
		i++;
	}
	return (i);
}

static unsigned int	exp_counter(unsigned int n)
{
	unsigned int	exp;
	unsigned int	digits;

	if (n == 0)
		return (1);
	digits = digit_counter(n);
	exp = 1;
	while (--digits)
		exp = exp * 10;
	return (exp);
}

int	pt_putunsigned(int out, unsigned int n)
{
	char				c;
	unsigned int		copy;
	int					i;
	unsigned int		exp;

	copy = n;
	exp = exp_counter(n);
	i = 0;
	while (exp > 0)
	{
		c = (copy / exp) + '0';
		if (write(out, &c, sizeof(char)) == -1)
			return (-1);
		copy = copy % exp;
		exp = exp / 10;
		i++;
	}
	return (i);
}
/*
int main()
{
    ft_putnbr_fd(INT_MIN, 1);
}
*/
