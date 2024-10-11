/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:00:53 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/11 14:23:31 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update the nexts and prevs, and then harakiri the node
void	delete_node(t_node **node)
{
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	node_free(node);
}

int	count_words(const char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if ((*str != ' ' && *str != '\t') && trigger == 0)
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

//Receives the Token node and moves the string that comes after around: the first word is
void	remove_redir(t_node *node)
{
	char	**buf;
	char	*tmp;
	int		i;
	
	//if (!node->next)
		//error_exit("parse error");
	buf = wordsplit(node->next->str);
	//if (!buf || !buf[0])
		//error_exit("split error"); TODO
	//Copy first word in token
	node->str = ft_strdup(buf[0]);
	i = 1;
	while (i <= count_words(node->next->str))
	{
		if (!node->prev)
		{
			node->next->str = ft_substr(node->next->str, ft_strlen(buf[0] + 1),\
			ft_strlen(node->next->str));
			break ;
		}
		tmp = node->prev->str;
		node->prev->str = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = node->prev->str;
		node->prev->str = ft_strjoin(tmp, buf[i]);
		free(tmp);
		i++;
	}
	//Si existe next next, me interesa modificar tambien su prev
	if (node->next->next)
		node->next->next->prev = node->prev;
	//TODO: borrar node->next sin LEAKS
	array_free(buf);
}
