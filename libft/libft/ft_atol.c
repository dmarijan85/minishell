/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:31:28 by dmarijan          #+#    #+#             */
/*   Updated: 2024/04/11 15:28:40 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	long	re;
	long	sign;

	i = 0;
	re = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n' \
			|| str[i] == '\r' || str[i] == '\f')
		i++;
	if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]) == 1)
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		re = (re * 10) + (str[i] - '0');
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i])
		return (2147483648);
	return (re * sign);
}
/*
int main()
{
	printf("%d", ft_atoi("0123"));
}
*/
