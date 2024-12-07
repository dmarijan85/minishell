/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   questions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:13:43 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/29 13:15:43 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	istoken(char *c, int i)
{
	if (c[i] == '|')
		return (1);
	else if (c[i] == '<')
	{
		if (isdouble(c + i, 0))
			return (3);
		return (2);
	}
	else if (c[i] == '>')
	{
		if (isdouble(c + i, 1))
			return (5);
		return (4);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' \
		|| c == '\f')
		return (1);
	return (0);
}

bool	isdouble(char *str, int lessorgreat)
{
	int	i;

	i = 0;
	if (lessorgreat == 0)
	{
		if (str[i + 1] == '<')
			return (true);
		return (false);
	}
	else
	{
		if (str[i + 1] == '>')
			return (true);
		return (false);
	}
	return (false);
}

bool	isbuiltin(t_msh *mini, char *name)
{
	char	**tmp;
	bool	re;

	re = false;
	tmp = wordsplit(mini, name, true);
	if (!tmp[0])
	{
		array_free(tmp);
		return (false);
	}
	if (!ft_strncmp(tmp[0], "export\0", 7) || !ft_strncmp(tmp[0], "exit\0", 5))
		re = true;
	else if (!ft_strncmp(tmp[0], "unset\0", 6))
		re = true;
	else if (!ft_strncmp(tmp[0], "pwd\0", 4))
		re = true;
	else if (!ft_strncmp(tmp[0], "cd\0", 3))
		re = true;
	else if (!ft_strncmp(tmp[0], "env\0", 4))
		re = true;
	else if (!ft_strncmp(tmp[0], "echo\0", 5))
		re = true;
	array_free(tmp);
	return (re);
}

int	isvalid(char *name)
{
	int	i;

	i = 0;
	if (!name || !*name || ft_isdigit(name[i]) || name[i] == '+' \
		|| name[i] == '=')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
		{
			if (name[i] == '=')
				break ;
			else if (name[i] == '+' && name[i + 1] == '=')
				break ;
			else if (!(name[i] == '_'))
				return (0);
		}
		i++;
	}
	return (1);
}
