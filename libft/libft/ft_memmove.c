/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:24:00 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:26:26 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}
/*
int main () {
   char str[10];
   char dst[10];

   strcpy(str,"AAAAAAAAA");
   strcpy(dst,"BBBBBBBBB");
   puts(str);
   puts(dst);

   ft_memmove(dst, str, 15);

   puts(str);
   puts(dst);

   return(0);
}
*/
