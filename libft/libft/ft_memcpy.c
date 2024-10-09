/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:56:50 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:26:20 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}

/*
int main () {
   char str[99];
   char dst[99];

   strcpy(str,"1234567890");
   strcpy(dst,"abcdefghij");
   puts(str);
   puts(dst);

   ft_memcpy(dst, str, 5);
   puts(dst);

   return(0);
}
*/
