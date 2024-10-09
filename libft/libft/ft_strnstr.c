/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:48:20 by dmarijan          #+#    #+#             */
/*   Updated: 2024/04/11 11:46:02 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_string(const char *to_find)
{
	size_t	size;

	size = 0;
	while (to_find[size] != '\0')
		size++;
	return (size - 1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!to_find[0])
		return ((char *)&str[0]);
	if (!str[0])
		return (0);
	j = 0;
	while (str[i] && ((i + j) <= n))
	{
		j = 0;
		while ((str[i + j] == to_find[j]) && ((i + j) < n))
		{
			if (j == count_string(to_find))
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

/*
int	main()
{
	char	s1[99];
	char	s2[99];

	strcpy(s1, "dxdmods");
	strcpy(s2, "xd");

	puts(ft_strnstr(s1, s2, 2));

}
*/
