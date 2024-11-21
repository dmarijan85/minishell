/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:04:52 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/21 15:33:20 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_envvar	*delete_envvar(t_envvar **node)
{
	t_envvar	*tmp;

	tmp = (*node)->prev;
	if (!tmp)
		tmp = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	free((*node)->name);
	if ((*node)->hasvalue)
		free((*node)->value);
	free((*node));
	node = NULL;
	return (tmp);
}

int	ft_argc(char **arr)
{
	int	argc;

	argc = 0;
	while (arr[argc])
		argc++;
	return (argc);
}

int	ft_nodesize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

