/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/21 15:34:21 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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

t_openmodes	setmode(t_node *node)
{
	if (node->token == LESS)
		return (READ);
	else if (node->token == GREAT)
		return (TRUNC);
	else if (node->token == GGREAT)
		return (APPEND);
	return (0);
}

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
		else if (temp->token == GREAT && temp->token == GGREAT \
			&& temp->token == LESS)
		{
			mode = setmode(temp);
			remove_redir(msh, temp);
			if (temp && temp->prev && temp->prev->token == 0)
				append_redirs((&temp->prev->redir), open_file(msh, temp->str, mode), mode, msh);
			else if (temp && temp->next && temp->next->token == 0)
				append_redirs((&temp->next->redir), open_file(msh, temp->str, mode), mode, msh);
			if (temp && !temp->prev)
				msh->list = temp->next;
			else
				delnext = true;
			delete_node(&temp);
		}
		else if (temp->token == PIPE)
		{
			msh->pipelen += 1;
			delete_node(&temp);
		}
		else if (temp->token == LLESS)
		{//TODO: maybe join it with the first if check
			remove_redir(msh, temp);
			here_doc(msh, temp);
			if (temp && temp->prev && temp->prev->token == 0)
				append_redirs((&temp->prev->redir), open_file(msh, ".heredoc", READ), READ, msh);
			else if (temp && temp->next && temp->next->token == 0)
				append_redirs((&temp->next->redir), open_file(msh, ".heredoc", READ), READ, msh);
			if (temp && !temp->prev)
				msh->list = temp->next;
			else
				delnext = true;
			delete_node(&temp);
		}
		temp = backup;
	}
}
