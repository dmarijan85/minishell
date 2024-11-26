/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoteshitbro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:41:56 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 14:43:55 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	isquote(char a)
{
	if (a == '\'' || a == '\"')
		return (1);
	else
		return (0);
}

int	istherequotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	howmanyquotes(char *str)
{
	int		i;
	int		quote;
	char	which;

	i = 0;
	quote = 0;
	while (!isquote(str[i]))
		i++;
	which = str[i];
	i = 0;
	while (str[i])
	{
		if (str[i] == which)
			quote++;
		i++;
	}
	return (quote);
}

char	imquoted(char *str, int loc)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i] && i <= loc)
	{
		if (isquote(str[i]) && !quote)
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				if (i == loc)
					return (quote);
				i++;
			}
			quote = '\0';
		}
		i++;
	}
	return (quote);
}
