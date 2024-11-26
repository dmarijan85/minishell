/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:48:49 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:49:14 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	stack_free_envvars(t_msh *mini)
{
	t_envvar	*tmp;
	t_envvar	*current;

	current = mini->envvar;
	if (!current)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		if (current->hasvalue)
			free(current->value);
		free(current);
		current = tmp;
	}
	mini->envvar = NULL;
}

void	stack_free_nodes(t_node **stack)
{
	t_node	*tmp;
	t_node	*current;

	current = *stack;
	if (!stack || !*stack)
		return ;
	while (current)
	{
		tmp = current->next;
		if (current->redir)
			stack_free_redirs(&current->redir);
		node_free(&current);
		current = tmp;
	}
	*stack = NULL;
}

void	stack_free_redirs(t_redirs **stack)
{
	t_redirs	*tmp;
	t_redirs	*current;

	current = *stack;
	if (!stack || !*stack)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}
