/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:17 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/22 16:23:54 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lo tengo aqui por referencia
/*
char	*get_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
*/

void	array_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			get_free(&str[i]);
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	node_free(t_node **stack)
{
	if (*stack)
	{
		if ((*stack)->str)
			free((*stack)->str);
		free(*stack);
	}
	*stack = NULL;
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

void	el_fregading(t_msh *mini)
{
	stack_free_nodes(&mini->list);
	free(mini->args);
	if (access(".heredoc", F_OK)) 
		do_last(mini, "rm -rf .heredoc", mini->env);
	wait(NULL);
}
