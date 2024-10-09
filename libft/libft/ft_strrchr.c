/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:49 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:28:02 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			while (i > 0)
			{
				s++;
				i--;
			}
			return ((char *) s);
		}
		i--;
	}
	return (NULL);
}

/*
//Find last occurrence of char c (passed as int) in string s.

int main () {
   char str[99];
   char dst[99];

   strcpy(str,"teste");
   puts(str);
   strcpy(dst, strrchr(str, 'x'));
   puts(dst);



   return(0);
}
*/
