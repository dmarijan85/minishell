/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildproject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 14:54:04 by dmarijan         ###   ########.fr       */
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
	char	*middlepart;
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
	middlepart = ft_strjoin(firstpart, value);
	result = ft_strjoin(middlepart, lastpart);
	free(firstpart);
	free(middlepart);
	free(lastpart);
	return (result);
}

char	*wildhandler(t_msh *mini, char *str, int stt, char *name)
{
	char		*ret;

	if (my_getenv(name, mini->env, mini->envvar))
	{
		ret = strexpander(mini, str, my_getenv(name, mini->env, mini->envvar), stt);		
		free(name);
		return (ret);
	}
	free(name);
	return (strexpander(mini, str, NULL, stt));
}

void	wildfinder(t_msh *mini, char **str, bool dofree)
{
	int		i;
	char	*res;
	char	*rec;
	char	*name;

	i = 0;
	rec = *str;
	while (i < (int)ft_strlen(rec) && rec[i])
	{
		if (rec[i] == '$' && imquoted(rec, i) != '\'')
		{
			name = ft_substr(rec, i + 1, expand_name_end(rec, i + 1) - i - 1);
			res = wildhandler(mini, *str, i, name);
			if (dofree)
				free(*str);
			*str = res;
		}
		i++;
		rec = *str;
	}
}
