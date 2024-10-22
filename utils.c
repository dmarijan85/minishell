/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:00:53 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/22 11:50:32 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fl_redir(t_redirs *current, t_openmodes mode)
{
	t_redirs	*tmp;

	tmp = current;
	if (!tmp && (mode == APPEND || mode == TRUNC))
		return (1);
	if (!tmp && (mode == READ))
		return (0);
	if (mode == APPEND || mode == TRUNC)
	{
		while (tmp && tmp->fd_type == READ)
			tmp = tmp->next;
		if (tmp && tmp->fd_type != READ)
			return (tmp->fd);
		return (1);
	}
	else
	{
		while (tmp && tmp->fd_type != READ)
			tmp = tmp->next;
		if (tmp && tmp->fd_type == READ)
			return (tmp->fd);
		return (0);
	}
	return (-1);
}

//update the nexts and prevs, and then harakiri the node
void	delete_node(t_node **node)
{
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	node_free(node);
	node = NULL;
}

int	count_words(const char *str)
{
	int	i;
	int	trigger;
	int	quote;

	i = 0;
	trigger = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && !quote)
		{
			quote = *str;
			trigger = 1;
			i++;
		}
		else if (*str == quote)
		{
			quote = 0;
			trigger = 0;
		}
		else if ((*str != ' ' && *str != '\t') && !trigger)
		{
			trigger = 1;
			i++;
		}
		else if ((*str == ' ' || *str == '\t') && !quote)
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
			tmp = node->next->str;
			node->next->str = ft_substr(node->next->str, ft_strlen(buf[0]) + 1,\
			ft_strlen(node->next->str));
			free(tmp);
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
	array_free(buf);
}


