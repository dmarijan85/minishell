/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:03 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/22 13:58:49 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_envvar	*find_first_envvar(t_envvar *current)
{
	if (!current)
		return (NULL);
	while (current->prev)
		current = current->prev;
	return (current);
}

t_envvar	*find_last_envvar(t_envvar *current)
{
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

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

bool	isbuiltin(t_msh *mini, char *name)
{
	char	**tmp;
	bool	re;

	re = false;
	tmp = wordsplit(mini, name, true);
	if (!ft_strncmp(tmp[0], "export\0", 7))
		re = true;
	else if (!ft_strncmp(tmp[0], "exit\0", 5))
		re = true;
	else if (!ft_strncmp(tmp[0], "unset\0", 6))
		re = true;
	else if (!ft_strncmp(tmp[0], "pwd\0", 4))
		re = true;
	else if (!ft_strncmp(tmp[0], "cd\0", 3))
		re = true;
	else if (!ft_strncmp(tmp[0], "env\0", 4))
		re = true;
	else if (!ft_strncmp(tmp[0], "echo\0", 5))
		re = true;
	array_free(tmp);
	return (re);
}

int	isvalid(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			if (!(name[i] == '_'))
				return (0);
		i++;
	}
	return (1);
}

void	append_envvar(t_envvar **stack, char *name, char *value, t_msh *mini)
{
	t_envvar	*node;
	t_envvar	*last_node;

	if (!isvalid(name))
		errexit(mini, "export: illegal variable name\n");
	node = malloc(sizeof(t_envvar));
	if (!node)
		errexit(mini, "t_envvar malloc failure?!\n");
	node->prev = NULL;
	node->next = NULL;
	node->name = name;
	node->hasvalue = false;
	if (value)
		node->hasvalue = true;
	node->value = value;
	if (!*stack)
		*stack = node;
	else
	{
		last_node = find_last_envvar(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
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

int	istoken(char *c, int i)
{
	if (c[i] == '|')
		return (1);
	else if (c[i] == '<')
	{
		if (isdouble(c + i, 0))
			return (2);
		return (1);
	}
	else if (c[i] == '>')
	{
		if (isdouble(c + i, 1))
			return (2);
		return (1);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' \
		|| c == '\f')
		return (1);
	return (0);
}

int	delim(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || !c)
		return (1);
	return (0);
}

int istheretokens(char *str)
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

char	plumbus(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (istoken(str, i))
		return (str[i]);
	while (str[i])
	{
		if (istoken(str, i))
		{
			i += istoken(str, i);
			while (ft_isspace(str[i]))
				i++;
			if (!str[i])
				return ('\n');
			else if (istoken(str, i))
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	quote_lexer(t_msh *mini, int end)
{
	char	*str;
	int		nquote;
	char	quote;

	quote = 0;
	nquote = 0;
	str = mini->args;
	while (str[end] && end < (int)ft_strlen(str) && str[end] != quote) 
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
		if (str[end] && str[end] != quote)
			end++;
	}
	if (nquote % 2)
		return (0);
	return (end);
}

void shrimp_lexer(t_msh *mini)
{
	int		stt;
	int		end;
	char	*str;
	char	tmp;

	str = mini->args;
	stt = 0;
	end = -1;
	if (istheretokens(str))
	{
		tmp = plumbus(str);		
		if (tmp)
		{
			if (tmp == '\n')
				ft_printf(2, "msh: syntax error near unexpected 'newline'.\n");
			else
				ft_printf(2, "msh: syntax error near unexpected '%c'.\n", tmp);
			mini->returnval = 2;
			return ;
		}
	}
	while (str && ++end < (int)ft_strlen(str))
	{
		if (str[end] == '\"' || str[end] == '\'')
		{
			end = quote_lexer(mini, end);
			if (!end)
				errexit(mini, "syntax error: unclosed quotes!\n");
		}
		if (str[end] == '|')
			stt = expand_list(ft_substr(str, stt, end - stt), PIPE, mini, &end) + 1;
		else if (str[end] == '<' && !isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LESS, mini, &end) + 1;
		else if (str[end] == '>' && !isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GREAT, mini, &end) + 1;
		else if (str[end] == '<' && isdouble(str + end, 0))
			stt = expand_list(ft_substr(str, stt, end - stt), LLESS, mini, &end) + 2;
		else if (str[end] == '>' && isdouble(str + end, 1))
			stt = expand_list(ft_substr(str, stt, end - stt), GGREAT, mini, &end) + 2;
		else if (!str[end + 1])
			stt = expand_list(ft_substr(str, stt, end - stt + 1), 0, mini, &end);
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
