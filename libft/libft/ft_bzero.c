/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:24:09 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:25:17 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
	return (s);
}

/*
int main () {
   char str[99];

   strcpy(str,"1234567890");
   puts(str);

   ft_bzero(str, 5);
   puts(str);

   return(0);
}
*/
