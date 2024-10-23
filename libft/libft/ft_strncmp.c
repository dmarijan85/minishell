/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:21:58 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/23 18:01:01 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	int	i;
	int	result;

	result = s1[0] - s2[0];
	if ((int)n <= 0)
		return (n);
	i = 0;
	while ((s1[i] || s2[i]) && i < (int)n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (result);
}
/*
int	main()
{
	printf("%d\n", strncmp("test\200", "test\0", 8));
}
*/
