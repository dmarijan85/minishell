/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/10 14:43:49 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_node	find_closest(t_node *temp)
{
	if (!temp->next)
		return (NULL); //parse error
	if (!temp->prev && temp->next->next->token == 0)
		return (temp->next->next);
	return (temp->prev);
}*/

//the parser will read from the list present at the general MSH struct and deal
//with the redirection nodes. This means:
//Create a new redirections list for each segment of our command input (each
//command between pipes), IF ANY.
//Correctly merge the command str, in case its interrupted by a redirection 
//(ex. "ls > hola -l").
//Related to last point, it will also delete the actual redirection node, 
//and if needed, delete any extra nodes currently present in the list
//(such as the ">" node and the "hola -l" node in the previous example. 
//The list thus simply becoming "ls -l").
void	parser(t_msh *msh)
{
	t_node	*temp;
	t_node	*closest;
	t_node	*backup;
	char	*str;

	temp = msh->list;
	closest = NULL;
	backup = NULL;
	if (temp)
	{
		while (temp)
		{	
			backup = temp;
			if (temp->token != 0)
			{
				//gotta figure out how to deal with pipes. probably not from here thats for sure
				if (temp->token == PIPE)
				{
					//do anything?
				}
				else if (temp->token == GREAT)
				{
					if (temp->prev && temp->prev->token == 0)
						append_redirs(temp->prev->redir, open_file(temp->str, TRUNC));
					else if (temp->next && temp->next->token == 0)
						append_redirs(temp->next->redir, open_file(temp->str, TRUNC));
					temp->prev->next = temp->next; //remove current token node.
					node_free(&temp);
				}
				else if (temp->token == GGREAT)
				{
					closest = find_closest(temp);
					if (closest)
						closest->fdout = open_file(temp->next->str, APPEND);
				}
				else if (temp->token == LESS)
				{
					closest = find_closest(temp);
					if (closest)
						closest->fdin = open_file(temp->next->str, OPEN);
				}
				else if (temp->token == LLESS)
				{
					//heredocs son los primeros en ser resueltos
					if (!temp->next)
						return ; //errexit (nos falta un delimitador)
					if (!temp->next->next)
						return ;
					//str = readline();
					//delete_next_node();
					temp->next->fdin = open_file(ft_strjoin(".heredoc", ft_itoa(msh->herectr)), TRUNC); //acordarse de cerrar el fd Y ADEMAS borrar el file temporal "heredoc*i*"
					ft_putstr_fd(str, temp->next->fdin);
					msh->herecounter++;
				}
			}
			temp = backup;
			temp = temp->next;
		}
	}
}
