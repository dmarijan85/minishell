/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:37:10 by dmarijan          #+#    #+#             */
/*   Updated: 2024/03/22 12:43:22 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	while (ft_strchr(set, *s1) && *s1)
		s1++;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && i > 0)
		i--;
	return (ft_substr(s1, 0, i + 1));
}

/*
int	main()
{
 	//char *s2 = "Hello \t  Please\n Trim me !";
	//printf("%zu", ft_strlen(" \n\t"));
 	
	char *ret = ft_strtrim(s1, " \n\t");	
	puts(ret);	
}
*/
