/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appends_balls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:12:37 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/27 17:51:24 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static void	those_who_toes(t_envvar *node, char *name)
{
	node->prev = NULL;
	node->next = NULL;
	node->name = name;
	node->hasvalue = false;
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
	those_who_toes(node, name);
	if (value)
	{
		node->hasvalue = true;
		removequotes(&value);
	}
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
