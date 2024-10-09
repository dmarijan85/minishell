/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:23:26 by dmarijan          #+#    #+#             */
/*   Updated: 2024/01/29 16:02:41 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	void	*new;
	t_list	*temp;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new = f(lst->content);
		temp = ft_lstnew(new);
		if (!temp)
		{
			del(new);
			ft_lstclear(&first, del);
		}
		ft_lstadd_back(&first, temp);
		lst = lst->next;
	}
	return (first);
}
