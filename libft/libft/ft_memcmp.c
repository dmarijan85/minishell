/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:31:44 by dmarijan          #+#    #+#             */
/*   Updated: 2024/09/25 14:18:05 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				result;
	unsigned char	*str1;
	unsigned char	*str2;

	result = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (result);
}

/* literally just strncmp but returns 1 if n is 0.
int	main()
{
	char	s1[99];
	char	s2[99];

	memcpy(s1, "Xa", 2);
	memcpy(s2, "Xb", 2);

	printf("%d", ft_memcmp(s1, s2, 2));

}
*/
