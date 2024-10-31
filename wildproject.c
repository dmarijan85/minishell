/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildproject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/31 13:37:06 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_name_end(char *str, int stt)
{
	int	end;

	end = stt;
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
	firstpart = malloc(stt + 1 * sizeof(char));
	//proc malloc
	while (str[++i] && str[i] != '$')
		firstpart[i] = str[i];
	firstpart[i] = '\0';
	end = expand_name_end(str, stt + 1);
	lastpart = malloc((ft_strlen(str) - stt + 1) * sizeof(char));
	//proc malloc
	i = -1;
	while (str[end])
		lastpart[++i] = str[end++];
	lastpart[++i] = '\0';
	result = ft_strjoin(ft_strjoin(firstpart, value), lastpart);
	free(firstpart);
	free(lastpart);
	return (result);
}

//asumo que j es el sitio en str donde esta el $ (lo llamo stt)
char	*wildhandler(t_msh *mini, char *str, int stt, char *name)
{
	t_envvar	*tmp;

	mini=mini; //TODO
	tmp = mini->envvar;
	if (getenv(name))
		return (strexpander(mini, str, getenv(name), stt));	//strexpander
	else
	{
		while (tmp)
		{
			if (!ft_strncmp(name, tmp->name, ft_strlen(name)))
			{
				free(name);
				return (strexpander(mini, str, tmp->value, stt));
			}
			tmp = tmp->next;
		}
	}
	free(name);
	return (strexpander(mini, str, NULL, stt)); //o str, no se muy bien
}

void	wildfinder(t_msh *mini, char **str)
{
	int		i;
	char	*res;
	char	*rec;
	char	*name;

	i = 0;
	rec = *str;
	while (rec[i])
	{
		if (rec[i] == '$')
		{
			name = ft_substr(rec, i + 1, expand_name_end(rec, i + 1) - i);
			res = wildhandler(mini, *str, i, name);
			*str = res;
		}
		i++;
	}
}
