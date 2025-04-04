/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:20:17 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:49:24 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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
		if (str)
			free(str);
	}
	str = NULL;
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

void	el_fregading(t_msh *mini)
{
	stack_free_nodes(&mini->list);
	free(mini->args);
	if (!access(".heredoc", F_OK))
	{
		do_last(mini, "rm -rf .heredoc");
		wait(NULL);
	}
}
