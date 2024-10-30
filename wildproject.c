/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildproject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/30 14:23:50 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_name_end(char *str, int stt)
{
	int	end;

	end = stt + 1;
	if (str[end] == '?')
		return (end);
	else if (str[end] && (ft_isalpha(str[end]) || str[end] == '_'))
	{
		while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
			end++;
		return (end);
	}
	else
		return (0);
}

char	*strexpander(t_msh *mini, char *str, char *value, int stt)
{
	char	*result;
	char	*firstpart;
	char	*lastpart;
	int		i;
	int		end;

	mini=mini;//TODO
	i = -1;
	firstpart = malloc(stt * sizeof(char));
	//proc malloc
	while (str[++i] && str[i] != '$')
		firstpart[i] = str[i];
	firstpart[i] = '\0';
	end = expand_name_end(str, stt);
	lastpart = malloc((ft_strlen(str) - end + 1) * sizeof(char));
	//proc malloc
	i = -1;
	while (str[end])
		lastpart[++i] = str[end++];
	lastpart[end] = '\0';
	result = ft_strjoin(ft_strjoin(firstpart, value), lastpart);
	free(firstpart);
	free(lastpart);
	return (result);
}

//asumo que j es el sitio en str donde esta el $ (lo llamo stt)
char	*wildhandler(t_msh *mini, char *str, int stt)
{
	t_envvar	*tmp;
	int			end;
	char		*name;

	mini=mini; //TODO
	tmp = mini->envvar;
	end = expand_name_end(str, stt);
	name = ft_substr(str, stt, end - stt);
	if (getenv(name))
		return (strexpander(mini, str, getenv(name), stt));	//strexpander
	else
	{
		while (tmp)
		{
			if (ft_strlen(name) == ft_strlen(tmp->name) && ft_strncmp(name, tmp->name, ft_strlen(name)))
				return (strexpander(mini, str, tmp->value, stt));
			tmp = tmp->next;
		}
	}
	return (NULL); // o str, no se muy bien
}

void	wildfinder(t_msh *mini, char **str)
{
	int		i;
	char	*res;
	char	*rec;

	i = 0;
	rec = *str;
	while (rec[i])
	{
		if (rec[i] == '$')
		{
			res = wildhandler(mini, *str, i);
			free(*str);
			*str = res;
		}
		i++;
	}
}
