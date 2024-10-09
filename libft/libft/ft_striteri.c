/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:56:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:27:33 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void next_char(unsigned int i, char *c)
{
    *c = *c + 1;
}

int main()
{
    char    s1[99];

    strcpy(s1, "ABCD");

    ft_striteri(s1, next_char);
	printf("%s", s1);
}
*/
