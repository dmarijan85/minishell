/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:42:36 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 14:42:57 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static void	removequotes_two(char *freer, char *tmp, char **str, int j)
{
	char	quote;
	int		i;

	i = 0;
	while (tmp[i])
	{
		quote = 0;
		if (isquote(tmp[i]))
		{
			quote = tmp[i];
			i++;
			while (tmp[i] && tmp[i] != quote)
				freer[j++] = tmp[i++];
		}
		else
			freer[j++] = tmp[i];
		i++;
	}
	freer[j] = '\0';
	free(*str);
	*str = freer;
}

void	removequotes(char **str)
{
	char	*tmp;
	char	*freer;

	tmp = *str;
	if (!istherequotes(tmp))
		return ;
	freer = malloc((ft_strlen(*str) - howmanyquotes(*str) + 1) * sizeof(char));
	if (!freer)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	removequotes_two(freer, tmp, str, 0);
}
