/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/14 14:16:15 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*find_first_node(t_node *current)
{
	if (!current)
		return (NULL);
	while (current->prev)
		current = current->prev;
	return (current);
}

void minishell_loop(t_msh *mini)
{
	msh_init(mini);
	mini->args = readline("msh$ ");
	shrimp_lexer(mini);
	parser(mini);
	if (mini->list)
		lebomboclaat(mini);
	if (mini->args && *(mini->args) && mini->herectr == 0)
		add_history(mini->args);
	t_node	*temp;
	int		i;

	i = 0;
	temp = mini->list;
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
	reset_msh(mini);
	minishell_loop(mini);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	mini;
	av = av;
	if (ac != 1)
		errexit(&mini, "Aquest programa no tolera arguments!! >:3\n");
	msh_start(&mini, envp);	
	do_last(&mini, "clear");
	wait(NULL);
	ft_printf(1, "\n\tT X I Q U I P E T X I N A !\n\n");
	minishell_loop(&mini);
}
