/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:36:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/11 12:35:07 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dsize;

	dsize = 0;
	while (dst[dsize] && dsize < dstsize)
		dsize++;
	i = dsize;
	while (src && src[dsize - i] && dsize + 1 < dstsize)
	{
		dst[dsize] = src[dsize - i];
		dsize++;
	}
	if (i < dstsize)
		dst[dsize] = '\0';
	return (i + ft_strlen(src));
}
/*
int     main()
{
	char	src[10] = "abcdefgh";
	char	dst[20] = "XXXXX";

	printf("%zu", strlcat(dst, src, 7));
	printf("%s", dst);

}
*/
