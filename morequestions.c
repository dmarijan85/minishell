/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morequestions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:40 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 13:16:51 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	istheretokens(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (istoken(str, i))
			return (1);
		i++;
	}
	return (0);
}

int	delim(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || !c)
		return (1);
	return (0);
}
