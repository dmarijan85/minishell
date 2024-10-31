/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildproject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/31 16:11:55 by dmarijan         ###   ########.fr       */
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
		//printf("start: %i end returned: %i\n", stt, end);
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
	//printf("firstpart: %s value: %s lastpart: %s\n", firstpart, value, lastpart);
	result = ft_strjoin(ft_strjoin(firstpart, value), lastpart);
	free(firstpart);
	free(lastpart);
	return (result);
}

char	*wildhandler(t_msh *mini, char *str, int stt, char *name)
{
	t_envvar	*tmp;

	mini=mini; //TODO
	tmp = mini->envvar;
	if (getenv(name))
		return (strexpander(mini, str, getenv(name), stt));
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
	return (strexpander(mini, str, NULL, stt));
}

void	wildfinder(t_msh *mini, char **str)
{
	int		i;
	char	*res;
	char	*rec;
	char	*name;

	i = 0;
	rec = *str;
	while (i < (int)ft_strlen(rec) && rec[i])
	{
		if (rec[i] == '$')
		{
			//printf("loop n%i before-> %s\n", i, *str);
			name = ft_substr(rec, i + 1, expand_name_end(rec, i + 1) - i - 1);
			//printf("supposed name: %s, its length: %li\n", name, ft_strlen(name));
			res = wildhandler(mini, *str, i, name);
			*str = res;
			//printf("loop n%i after -> %s\n", i, *str);
		}
		i++;
		rec = *str;
	}
}
