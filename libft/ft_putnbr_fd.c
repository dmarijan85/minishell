/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:28:02 by dmarijan          #+#    #+#             */
/*   Updated: 2024/03/21 13:43:44 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digit_counter(int n)
{
	int	i;
	int	copy;

	i = 0;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	copy = n;
	while (copy > 0)
	{
		copy = copy / 10;
		i++;
	}
	return (i);
}

static int	exp_counter(int n)
{
	int	exp;
	int	digits;

	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (1000000000);
	digits = digit_counter(n);
	if (n < 0)
		digits--;
	exp = 1;
	while (--digits)
		exp = exp * 10;
	return (exp);
}

static int	retmin(int n)
{
	if (n == INT_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	return (0);
}

static int	isneg(int *copy)
{
	*copy = *copy * -1;
	return (write (1, "-", sizeof(char)));
}

int	pt_putnbr_fd(int n)
{
	char	c;
	int		copy;
	int		i;
	int		exp;

	copy = n;
	exp = exp_counter(n);
	i = 0;
	if (n == INT_MIN)
		return (retmin(n));
	else if (n < 0)
		i = isneg(&copy);
	while (exp > 0 && n != INT_MIN && i >= 0)
	{
		c = (copy / exp) + '0';
		if (write(1, &c, sizeof(char)) == -1)
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
