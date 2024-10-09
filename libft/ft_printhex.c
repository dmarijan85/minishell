/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:50:43 by dmarijan          #+#    #+#             */
/*   Updated: 2024/03/21 13:47:42 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printc(int c)
{
	return (write(1, &c, sizeof(char)));
}

static void	checkflag(char flag, int *letter)
{
	if (flag == 'x')
		*letter = 'a';
	else if (flag == 'X')
		*letter = 'A';
}

int	pt_puthex(char flag, unsigned int n)
{
	int	rv;
	int	letter;
	int	temp;

	rv = 0;
	checkflag(flag, &letter);
	if ((n / 16) > 0)
		rv += pt_puthex(flag, n / 16);
	if (rv < 0)
		return (-1);
	if ((n % 16) >= 10 && (n % 16) <= 15)
	{
		temp = printc(letter + ((n % 16) - 10));
		if (temp == -1)
			return (-1);
		rv += temp;
	}
	else
	{
		temp = printc('0' + (n % 16));
		if (temp == -1)
			return (-1);
		rv += temp;
	}
	return (rv);
}
