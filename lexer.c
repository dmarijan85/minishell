/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:03 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/16 18:25:35 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirs	*find_last_redirs(t_redirs *current)
{
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

t_node	*find_last_node(t_node *current)
{
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

//puts new node as first if its the first one in stack (if **stack is empty)
//OR correctly appends new node as last of the list.
void	append_redirs(t_redirs **stack, int fd, t_openmodes type)
{
	t_redirs	*node;
	t_redirs	*last_node;

	node = malloc(sizeof(t_redirs));
	if (!node)
		return ; //errexit with cleaning funcs
	node->next = NULL;
	node->fd = fd;
	node->fd_type = type;
	if (!*stack)
		*stack = node;
	else
	{
		last_node = find_last_redirs(*stack);
		last_node->next = node;
	}
}

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
/*
char	*removequotes(char *str)
{
	char	*tmp;

	if (str[1] == '\"' || str[1] == '\'')
		return (NULL);
	tmp = ft_substr(str + 1, 0, ft_strlen(str) - 1);
	free(str);
	return (tmp);
}
*/
int expand_list(char *str, t_tokens token, t_node **first, int *end)
{
	if (str && *str)
	{
		//if (*str == '\'' || *str == '\"')
			//str = removequotes(str);
		append_node(first, str, 0);
	}
	if (token != 0)
		append_node(first, NULL, token);
	if (token == LLESS || token == GGREAT)
		*end = *end + 1;
	return (*end);
}
//this lexer is going through the raw input string and reading character by character. It will create the first version of
//our linked list, ready to be passed to the parser. Upon finding one of the following tokens: > < >> << |, it will create
//TWO nodes at the same time, one for the stuff to the left of the found token (if anything), and one for the singular token.
//this behavior is exactly the same for each token, the only differences being the indexes it reads from to account for >> and <<.
//all of this is automatically assigned to the pointer of the list in our general MSH struct. 

int	delim(char	c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || !c)
		return (1);
	return (0);
}

int	quote_lexer(t_msh *mini, int end)
{
	char	*str;
	int		nquote;
	char	quote;

	nquote = 0;
	str = mini->args;
	while (end < (int)ft_strlen(str) && !delim(str[end]))
	{
		if (str[end] == '\"' || str[end] == '\'')
		{
			quote = str[end];
			nquote++;
			end++;
			while (str[end] && str[end] != quote)
				end++;
			if (!str[end])
				return (0);
			nquote++;
		}
		end++;
	}
	if (nquote % 2)
		return (0);
	return (end);
}

void shrimp_lexer(t_msh *mini)
{
	int		stt; //start
	int		end;
	t_node	**beg;
	char	*str;

	str = mini->args;
	beg = &mini->list;
	stt = 0;
	end = 0;
	while (str && end < (int)ft_strlen(str))
	{
		if (str[end] == '\"' || str[end] == '\'')
		{
			end = quote_lexer(mini, end);
			if (!end)
				errexit(mini, "You can't leave any unopened quotes!\n");
			stt = expand_list(ft_substr(str, stt, end - stt), 0, beg, &end);
		}
		else if (str[end] == '|')
			stt = expand_list(ft_substr(str, stt + 1, end - stt - 2), PIPE, beg, &end) + 1;
		else if (str[end] == '<' && !isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LESS, beg, &end) + 1;
		else if (str[end] == '>' && !isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GREAT, beg, &end) + 1;
		else if (str[end] == '<' && isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LLESS, beg, &end) + 2;
		else if (str[end] == '>' && isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GGREAT, beg, &end) + 2;
		else if (!str[end + 1] && end != 0)
			stt = expand_list(ft_substr(str, stt, end - stt + 1), 0, beg, &end);
		end++;
	}
}
/*
	t_node	*temp;
	int		i;

	i = 0;
	temp = *beg;
	if (temp)
	{
		while (temp->next)
		{
			if (temp->str)
				printf("Node STR %i: %s\n", i, temp->str);
			if (temp->token)
				printf("Node TKN %i: %i\n", i, temp->token);
			if (temp->redir)
				printf("Node %i has REDIR\n", i);
			temp = temp->next;
			i++;
		}
		if (temp->str)
			printf("NODE STR %i: %s\n", i, temp->str);
		if (temp->token)
			printf("NODE TKN %i: %i\n", i, temp->token);
		if (temp->redir)
			printf("Node %i has REDIR\n", i);
	}	
}*/
