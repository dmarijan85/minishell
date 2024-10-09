/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:19:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/02/02 17:37:37 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	letter;

	letter = (char) c;
	while (letter != *s && *s)
		s++;
	if (letter == *s)
		return ((char *)s);
	return (NULL);
}

/*	Finds first occurrence of char c (passed as int) in string s).
int main () {
   char str[99];
   char	dst[99];

   strcpy(str,"lmao ejemplo");
   puts(str);

   strcpy(dst, ft_strchr(str, '\0'));
   puts(dst);

   return(0);
}
*/
