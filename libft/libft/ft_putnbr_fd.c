/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:28:02 by dmarijan          #+#    #+#             */
/*   Updated: 2024/09/25 14:17:41 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		copy;
	int		exp;

	copy = n;
	exp = exp_counter(n);
	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", sizeof(char));
		copy = copy * -1;
	}
	while (exp > 0 && n != INT_MIN)
	{
		c = (copy / exp) + '0';
		write(fd, &c, sizeof(char));
		copy = copy % exp;
		exp = exp / 10;
	}
}
/*
int main()
{
    ft_putnbr_fd(INT_MIN, 1);
}
*/
