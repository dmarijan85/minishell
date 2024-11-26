/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:00:53 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/26 16:54:03 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	fl_redir(t_redirs *current, t_openmodes mode)
{
	t_redirs	*tmp;

	tmp = fl_findlast(current, mode);
	if (!tmp && (mode == APPEND || mode == TRUNC))
		return (1);
	if (!tmp && (mode == READ))
		return (0);
	else
		return (tmp->fd);
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

int	count_words(const char *str, int i, int trigger, int quote)
{
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

static void	node_prev_is_no(t_node *node, char **buf)
{
	char	*tmp;

	tmp = node->next->str;
	node->next->str = ft_substr(node->next->str, \
		ft_strlen(buf[0]) + 1, ft_strlen(node->next->str));
	free(tmp);
}

void	remove_redir(t_msh *mini, t_node *node, int i)
{
	char	**buf;
	char	*tmp;

	buf = wordsplit(mini, node->next->str, true);
	if (!buf || !buf[0])
		errexit(mini, "Remove Redir Error?!, wordsplit blew the fuck up?\n");
	node->str = ft_strdup(buf[0]);
	while (i <= count_words(node->next->str, 0, 0, 0))
	{
		if (!node->prev)
		{
			node_prev_is_no(node, buf);
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
