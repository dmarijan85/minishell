/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:35:53 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:27:41 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	int		tot;

	tot = ft_strlen(s1) + ft_strlen(s2);
	nstr = malloc(tot + 1 * sizeof(char));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1, tot + 1);
	ft_strlcat(nstr, s2, tot + 1);
	nstr[tot] = '\0';
	return (nstr);
}
/*
int	main()
{
	//char *s1 = "";
 	//char *s2 = " ";
 	//char *s3 = "";
 	char *res = ft_strjoin("a", "");

	printf("%s \n", res);
}
*/
