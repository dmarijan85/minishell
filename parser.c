/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:18 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/09 16:08:04 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	find_closest(t_node *temp) //nos encuentra el comando mas cercano. util para redirecciones
{
	if (!temp->next)
		return (NULL); //parse error
	if (!temp->prev && temp->next->next->token == 0) // caso si tenemos el comando a la derecha > lol cat
		return (temp->next->next);
	return (temp->prev);
}

void	parser(t_msh *msh)
{
	t_node	*temp;
	t_node	*closest;
	char	*str;

	temp = msh->list;
	closest = NULL;
	if (temp)
	{
		while (temp)
		{
			if (temp->token != 0)
			{
				// split token node into the actual redirection + filename and either CREATE or JOIN the remainder of the text onto the closest command node.
				if (temp->token == PIPE)
				{
					if (!temp->prev)
						return ;//error exit
					if (!temp->next)
						append_node(&temp, readline("> "), 0);
					temp->prev->fdout = -1;//flag para pipe[0]
					temp->next->fdin =  -2;//flag para pipe[1]
				}
				else if (temp->token == GREAT)
				{
					if (temp->prev && temp->prev->token == 0)
						append_redirs(temp->prev->redir, open_file(temp->str, TRUNC));
					else if (temp->next && temp->next->token == 0)
						append_redirs(temp->next->redir, open_file(temp->str, TRUNC));
				}
				else if (temp->token == GGREAT)
				{
					closest = find_closest(temp);
					if (closest)
						closest->fdout = open_file(temp->next->str, APPEND); //ACORDAR DE HACER CLOSE (same as great)
				}
				else if (temp->token == LESS)
				{
					closest = find_closest(temp);
					if (closest)
						closest->fdin = open_file(temp->next->str, OPEN); //remember to close
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
			temp = temp->next;
		}
	}
}
