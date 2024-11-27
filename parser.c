/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/27 17:30:32 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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

static void	here_doctor_help_us(t_msh *msh, t_node *temp, bool *delnext)
{
	remove_redir(msh, temp, 1);
	wait_signal(-1);
	here_doc(msh, temp);
	if (temp && temp->prev && temp->prev->token == 0)
		append_redirs((&temp->prev->redir), open_file(msh, ".heredoc", READ), \
			READ, msh);
	else if (temp && temp->next && temp->next->token == 0)
		append_redirs((&temp->next->redir), open_file(msh, ".heredoc", READ), \
			READ, msh);
	if (temp && !temp->prev)
		msh->list = temp->next;
	else
		*delnext = true;
	delete_node(&temp);
	wait_signal(1);
}

static void	handle_scenario(t_msh *msh, t_node *temp, bool *delnext)
{
	t_openmodes	mode;

	mode = setmode(temp);
	remove_redir(msh, temp, 1);
	if (temp && temp->prev && temp->prev->token == 0)
		append_redirs((&temp->prev->redir), open_file(msh, temp->str, mode), \
			mode, msh);
	else if (temp && temp->next && temp->next->token == 0)
		append_redirs((&temp->next->redir), open_file(msh, temp->str, mode), \
			mode, msh);
	if (temp && !temp->prev)
		msh->list = temp->next;
	else
		*delnext = true;
	delete_node(&temp);
}

static void	peep_my_pipe(t_msh *msh, t_node *temp)
{
	msh->pipelen += 1;
	delete_node(&temp);
}

void	parser(t_msh *msh)
{
	t_node		*temp;
	t_node		*backup;
	bool		delnext;

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
		else if (temp->token == GREAT || temp->token == GGREAT \
			|| temp->token == LESS)
			handle_scenario(msh, temp, &delnext);
		else if (temp->token == PIPE)
			peep_my_pipe(msh, temp);
		else if (temp->token == LLESS)
			here_doctor_help_us(msh, temp, &delnext);
		temp = backup;
	}
}
