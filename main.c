/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/16 15:17:20 by dmarijan         ###   ########.fr       */
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
	int	i = 0;
	while (i < 3)
	{
		mini->args = readline("testing...> ");
		shrimp_lexer(mini->args, &mini->list);
		parser(mini);
		lebomboclaat(mini);
//		add_history(args); (mirar man?)
		reset_msh(mini);
		i++;
	}
}	

int	main(int ac, char **av, char **envp)
{
	t_msh	mini;

	av = av;
	if (ac != 1)
	{
		printf("This program does not accept arguments!! >:3\n");
		exit(0);
	}
	mini.env = envp;
	mini.list = NULL;
	mini.reset = false;
	mini.herectr = 0;
	mini.args = NULL;
	mini.pipelen = 0;

	printf("Benvingut a la xiquipetxina!\n");
	minishell_loop(&mini);
	//readline tiene 204.000 bytes de leaks, ignoralos :sob:
	t_node		*temp;
	t_redirs	*redir;
	int		i;

	i = 0;
	temp = mini.list;
	if (temp)
	{
		while (temp)
		{
			redir = temp->redir;
			if (temp->str)
				ft_printf("Node STR %i: %s\n", i, temp->str);
			if (temp->token)
				ft_printf("Node TKN %i: %i\n", i, temp->token);
			while (redir)
			{
				redir = temp->redir;
				ft_printf("The Node %i has REDIR: %i\n", i, redir->fd_type);
				redir = redir->next;
			}
			temp = temp->next;
			i++;
		}
	}
	reset_msh(&mini);
}
