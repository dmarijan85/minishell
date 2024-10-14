/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/14 14:07:26 by mclaver-         ###   ########.fr       */
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
	t_node		*temp;
	t_node		*backup;
	bool		delnext;
	t_openmodes	mode;

	temp = msh->list;
	delnext = false;
	while (temp)
	{	
		backup = temp->next;
		if (delnext)
		{
			delete_node(&temp);
			delnext = false;
		}
		else if (temp->token != 0 && temp->token != PIPE \
			&& temp->token != LLESS)
		{
			if (temp->token == LESS)
				mode = READ;
			else if (temp->token == GREAT)
				mode = TRUNC;
			else if (temp->token == GGREAT)
				mode = APPEND;
			remove_redir(temp);
			if (temp->prev && temp->prev->token == 0)
				append_redirs((&temp->prev->redir), open_file(temp->str, mode), mode);
			else if (temp->next && temp->next->token == 0)
				append_redirs((&temp->next->redir), open_file(temp->str, mode), mode);
			if (!temp->prev)
				msh->list = temp->next;
			else
				delnext = true;
			delete_node(&temp);
		}
		else if (temp->token == PIPE)
		{
			if (!temp->prev)
				return ;//error_exit(parseerror pipe);
			if (!temp->next)
				return ;//miniheredoc, con delim '\n'
			msh->pipelen += 1;
			delete_node(&temp);
		}
		else if (temp->token == LLESS)
		{
			return ; //miniheredoc con limitador de temp->next->str
		}
		temp = backup;
	}
}

