/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:16:02 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/31 14:41:32 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		write(fd, &s[i], sizeof(char));
		i++;
	}
}
/*
int main()
{
    char	*new;

	new = malloc(5 * sizeof(char));
	strcpy(new, "LMAO");
	ft_putstr_fd(new, 0);
}
*/
