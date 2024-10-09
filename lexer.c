/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:03 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/09 16:08:06 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*find_last_node(t_node *current)
{
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}
/*
//puts new node as first if its the first one in stack (if **stack is empty)
//OR correctly appends new node as last of the list.
void	append_redirs(t_redirs **stack, int fd)
{
	t_redirs	*node;
	t_redirs	*last_node;

	node = malloc(sizeof(t_redirs));
	if (!node)
		return ; //errexit with cleaning funcs
	node->next = NULL;
	if (fd)
		node->fd = fd;
	if (!*stack)
		*stack = node;
	else
	{
		last_node = find_last_node(*stack);
		last_node->next = node;
	}
}*/

//puts new node as first if its the first one in stack (if **stack is empty)
//OR correctly appends new node as last of the list.
void	append_node(t_node **stack, char *str, t_tokens token)
{
	t_node	*node;
	t_node	*last_node;

	node = malloc(sizeof(t_node));
	if (!node)
		return ; //errexit with cleaning funcs
	node->next = NULL;
	node->redir = NULL;
	node->str = str;
	node->token = token;
	if (!*stack)
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

bool isdouble(char *str, int lessorgreat)
{
	int	i;

	i = 0;
	if (lessorgreat == 0)
	{
		if (str[i + 1] == '<')
			return (true);
		return (false);
	}
	else
	{
		if (str[i + 1] == '>')
			return (true);
		return (false);
	}
	return (false);
}

int expand_list(char *str, t_tokens token, t_node **first, int *end)
{
	if (str && *str)
		append_node(first, str, 0);
	if (token != 0)
		append_node(first, NULL, token);
	if (token == 3 || token == 5)
		*end = *end + 1;
	return (*end);
}

void lexer(char *str, t_node *beg)
{
	int		stt; //start
	int		end;
	bool	opquote;

	stt = 0;
	end = 0;
	opquote = false;
	while (str[end])
	{
		if (str[end] == '"' && opquote == true)
			opquote = false;
		else if (str[end] == '"')
			opquote = true;
		else if (str[end] == '|' && opquote == false)
			stt = expand_list(ft_substr(str, stt, end), PIPE, &beg, &end) + 1;
		else if (str[end] == '<' && opquote == false && !isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end), LESS, &beg, &end) + 1;
		else if (str[end] == '>' && opquote == false && !isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end), GREAT, &beg, &end) + 1;
		else if (str[end] == '<' && opquote == false && isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end), LLESS, &beg, &end) + 2;
		else if (str[end] == '>' && opquote == false && isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end), GGREAT, &beg, &end) + 2;
		else if (!str[end + 1] && end != 0)
			stt = expand_list(ft_substr(str, stt, end + 1), 0, &beg, &end);
		end++;
	}
	t_node	*temp;
	int		i;

	i = 0;
	temp = beg;
	if (temp)
	{
		while (temp->next)
		{
			ft_printf("Node STR %i: %s\n", i, temp->str);
			ft_printf("Node TKN %i: %i\n", i, temp->token);
			temp = temp->next;
			i++;
		}
		ft_printf("NODE STR %i: %s\n", i, temp->str);
		ft_printf("NODE TKN %i: %i\n", i, temp->token);
	}
}
