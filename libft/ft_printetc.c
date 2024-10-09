/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printetc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:09:01 by dmarijan          #+#    #+#             */
/*   Updated: 2024/03/21 13:47:10 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pt_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	pt_putstr(char *s)
{
	size_t	i;
	int		temp;

	i = 0;
	if (!s)
		return (pt_putstr("(null)"));
	while (i < pt_strlen(s))
	{
		temp = write(1, &s[i], sizeof(char));
		if (temp == -1)
			return (-1);
		i++;
	}
	return (i);
}

char	*pt_strchr(const char *s, int c)
{
	char	letter;

	letter = (char) c;
	while (letter != *s && *s)
		s++;
	if (letter == *s)
		return ((char *)s);
	return (NULL);
}
