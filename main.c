/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:25:37 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/17 14:32:41 by dmarijan         ###   ########.fr       */
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
	mini->args = get_next_line(0);
	shrimp_lexer(mini);
	parser(mini);
	if (mini->list)
		lebomboclaat(mini);
//	add_history(args); (mirar man?)
//	reset_msh(mini);
//	minishell_loop(mini);
}	

int	main(int ac, char **av, char **envp)
{
	t_msh	mini;
	int		j = 0;

	mini.env = envp;
	mini.list = NULL;
	mini.reset = false;
	mini.herectr = 0;
	mini.args = NULL;
	mini.pipelen = 0;
	av = av;
	if (ac != 1)
		errexit(&mini, "This program does not accept arguments!! >:3\n");
	do_last(&mini, "clear", mini.env);//limpia la pantalla al ejecutar y queda tope limpio :3
	wait(NULL);
	printf("Benvingut a la xiquipetxina!\n");
	while (j < 3)
	{
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
	j++;
	}
}
