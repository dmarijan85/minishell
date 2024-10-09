/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:31:11 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:28:18 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*nstr;
	int		i;

	i = 0;
	nstr = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!nstr)
		return (NULL);
	while (s[i])
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
/*
char next_char(unsigned int i, char c)
{
	char	nchar;

	nchar = c + 1;

	return (nchar);
}

int main()
{
    char    s1[99];

    strcpy(s1, "ABCD");
	
	printf("%s", ft_strmapi(s1, next_char));
}
*/
