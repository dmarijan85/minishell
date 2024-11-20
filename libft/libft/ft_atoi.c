/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:47:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/20 17:35:11 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	re;
	int	sign;

	i = 0;
	re = 0;
	sign = 1;
	if (!str)
		return (0);
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
	return (re * sign);
}
/*
int main()
{
	printf("%d", ft_atoi("0123"));
}
*/
