/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:20:56 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/25 13:26:41 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		write(fd, &s[i], sizeof(char));
		i++;
	}
	write(fd, "\n", sizeof(char));
}
/*
int main()
{
    char    *new;

    new = malloc(5 * sizeof(char));
    strcpy(new, "LMAO");
    ft_putendl_fd(new, 0);
	ft_putendl_fd(new, 0);
}
*/
