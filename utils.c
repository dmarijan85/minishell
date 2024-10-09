/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:00:53 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/09 16:44:34 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if ((*str != ' ' || *str != '\t') && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == ' ' || *str == '\t')
			trigger = 0;
		str++;
	}
	return (i);
}

//Receives the Token node and moves the string that comes after around
void	remove_redir(t_node *node)//
{
	char	**buf;
	int		i;
	//if (!node->next)
		//error_exit("parse error")
	buf = wordsplit(node->next->str);
	//Copy first word in token
	ft_strlcpy(node->str, buf[0], ft_strlen(buf[0]));
	i = 1;
	while (i <= count_words(node->next->str))
	{
	//si no hay prev no borres node->next, y simplemente solo quita la primera palabra
		if (!node->prev)
		{
			node->next->str = substr(node->next->str, ft_strlen(buf[0] + 1,
				ft_strlen(node->next->str));
			break ;
		}
		node->prev->str = ft_strjoin(node->prev->str, " ");
		node->prev->str = ft_strjoin(node->prev->str, buf[i]);
		i++;
	}
	node->prev->next = node->next->next;

}
