/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildproject.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:08 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 12:45:51 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	expand_name_end(char *str, int stt)
{
	int	end;

	end = stt;
	if (str[end] == '?')
		return (end + 1);
	else if (str[end] && (ft_isalpha(str[end]) || str[end] == '_'))
	{
		while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
			end++;
		return (end);
	}
	return (end + 1);
}

char	*strexpander_two(char *firstpart, char *lastpart, int end, char *value)
{
	char	*middlepart;
	char	*result;

	end = end;
	middlepart = ft_strjoin(firstpart, value);
	result = ft_strjoin(middlepart, lastpart);
	free(firstpart);
	free(middlepart);
	free(lastpart);
	return (result);
}

char	*strexpander(t_msh *mini, char *str, char *value, int stt)
{
	char	*firstpart;
	char	*lastpart;
	int		i;
	int		end;

	i = -1;
	firstpart = malloc(stt + 1 * sizeof(char));
	if (!firstpart)
		errexit(mini, "malloc failure?!\n");
	while (str[++i] && str[i] != '$')
		firstpart[i] = str[i];
	firstpart[i] = '\0';
	end = expand_name_end(str, stt + 1);
	lastpart = malloc((ft_strlen(str) - stt + 1) * sizeof(char));
	if (!lastpart)
	{
		free(firstpart);
		errexit(mini, "malloc failure?!\n");
	}
	i = -1;
	while (str[end])
		lastpart[++i] = str[end++];
	lastpart[++i] = '\0';
	return (strexpander_two(firstpart, lastpart, end, value));
}

char	*wildhandler(t_msh *mini, char *str, int stt, char *name)
{
	char		*ret;
	char		*retval;

	if (*name == '?' && !(*name) + 1)
	{
		retval = ft_itoa(mini->returnval);
		ret = strexpander(mini, str, retval, stt);
		free(retval);
		return (ret);
	}
	else if (my_getenv(name, mini->env, mini->envvar))
	{
		ret = strexpander(mini, str, my_getenv(name, mini->env, \
			mini->envvar), stt);
		return (ret);
	}
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
			free(name);
			if (dofree)
				free(*str);
			*str = res;
		}
		i++;
		rec = *str;
	}
}
