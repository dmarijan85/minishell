//ponme el stdheader pls

#include "minishell.h"

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

