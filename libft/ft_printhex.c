/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:50:43 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 12:19:53 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printc(int out, int c)
{
	return (write(out, &c, sizeof(char)));
}

static void	checkflag(char flag, int *letter)
{
	if (flag == 'x')
		*letter = 'a';
	else if (flag == 'X')
		*letter = 'A';
}

int	pt_puthex(int out, char flag, unsigned int n)
{
	int	rv;
	int	letter;
	int	temp;

	rv = 0;
	checkflag(flag, &letter);
	if ((n / 16) > 0)
		rv += pt_puthex(out, flag, n / 16);
	if (rv < 0)
		return (-1);
	if ((n % 16) >= 10 && (n % 16) <= 15)
	{
		temp = printc(out, letter + ((n % 16) - 10));
		if (temp == -1)
			return (-1);
		rv += temp;
	}
	else
	{
		temp = printc(out, '0' + (n % 16));
		if (temp == -1)
			return (-1);
		rv += temp;
	}
	return (rv);
}
