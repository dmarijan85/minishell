/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:03 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/21 12:53:35 by mclaver-         ###   ########.fr       */
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
void	append_redirs(t_redirs **stack, int fd, t_openmodes type, t_msh *mini)
{
	t_redirs	*node;
	t_redirs	*last_node;

	node = malloc(sizeof(t_redirs));
	if (!node)
		errexit(mini, "t_redirs malloc failure?!\n");
	node->next = NULL;
	node->fd = fd;
	node->fd_type = type;
	node->mini = mini;
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
void	append_node(t_node **stack, char *str, t_tokens token, t_msh *mini)
{
	t_node	*node;
	t_node	*last_node;

	node = malloc(sizeof(t_node));
	if (!node)
		errexit(mini, "t_node malloc failure?!\n");
	node->next = NULL;
	node->redir = NULL;
	node->str = str;
	node->token = token;
	node->mini = mini;
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

void	removequotes(char **str)
{
	char	*tmp;
	char	*freer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	freer = malloc((ft_strlen(*str) - 1) * sizeof(char));
	tmp =  *str;
	while (tmp[i] && tmp[i] != '\"' && tmp[i] != '\'')
		freer[j++] = tmp[i++];
	i++;
	while (tmp[i] && tmp[i] != '\"' && tmp[i] != '\'')
		freer[j++] = tmp[i++];
	freer[j] = '\0';
	tmp = *str;
	free(tmp);
	*str = freer;
}

int istherequotes(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int expand_list(char *str, t_tokens token, t_msh *mini, int *end)
{
	
	if (str && *str)
	{
		//if (istherequotes(str))
			//removequotes(&str);
		append_node(&mini->list, str, 0, mini);
	}
	if (token != 0)
		append_node(&mini->list, NULL, token, mini);
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
	char	*str;

	str = mini->args;
	stt = 0;
	end = 0;
	while (str && end < (int)ft_strlen(str))
	{
		if (str[end] == '\"' || str[end] == '\'')
		{
			end = quote_lexer(mini, end);
			if (!end)
				errexit(mini, "syntax error: unclosed quotes!\n");
			stt = expand_list(ft_substr(str, stt, end - stt), 0, mini, &end);
		}
		else if (str[end] == '|')
			stt = expand_list(ft_substr(str, stt, end - stt), PIPE, mini, &end) + 1;
		else if (str[end] == '<' && !isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LESS, mini, &end) + 1;
		else if (str[end] == '>' && !isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GREAT, mini, &end) + 1;
		else if (str[end] == '<' && isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LLESS, mini, &end) + 2;
		else if (str[end] == '>' && isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GGREAT, mini, &end) + 2;
		else if (!str[end + 1] && end != 0)
			stt = expand_list(ft_substr(str, stt, end - stt + 1), 0, mini, &end);
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
