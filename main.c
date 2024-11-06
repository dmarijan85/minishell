/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/06 14:43:10 by dmarijan         ###   ########.fr       */
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

void msh_init(t_msh *mini)
{
	mini->list = NULL;
	mini->reset = false;
	mini->herectr = 0;
	mini->args = NULL;
	mini->pipelen = 0;
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
	mini.env = envp;
	mini.envismallocd = false;
	mini.pwd = getenv("PWD");
	if (!mini.pwd)
		errexit(&mini, "Va no em toquis els qllons germanet\n");
	do_last(&mini, "clear", mini.env);//limpia la pantalla al ejecutar y queda tope limpio :3
	wait(NULL);
	printf("\n\tT X I Q U I P E T X I N A !\n\n");
	mini.envvar = NULL;
	minishell_loop(&mini);
}
