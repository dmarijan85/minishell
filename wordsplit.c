/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:09 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/29 16:15:59 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isquote(char a)
{
	if (a == '\'' || a == '\"')
		return (1);
	else
		return (0);
}

int istherequotes(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (isquote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	howmanyquotes(char *str)
{
	int		i;
	int		quote;
	char	which;

	i = 0;
	quote = 0;
	while (!isquote(str[i]))
		i++;
	which = str[i];
	i = 0;
	while (str[i])
	{
		if (str[i] == which)
			quote++;
		i++;
	}
	return (quote);
}

char imquoted(char *str, int loc)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && i <= loc)
	{
		if (isquote(str[i]) && !quote)
		{
			quote = str[i];
			while (str[i] != quote)
			{
				if (i == loc)
					return (quote);
				i++;
			}
			quote = 0;
		}
		i++;
	}
	return (0);
}

void	removequotes(char **str)
{
	char	*tmp;
	char	*freer;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	tmp = *str;
	if (!istherequotes(tmp))
		return ;
	freer = malloc((ft_strlen(*str) - howmanyquotes(*str) + 1) * sizeof(char));
	if (!freer)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	while (tmp[i])
	{
		quote = 0;
		if (isquote(tmp[i]))
		{
			quote = tmp[i];
			i++;
			while (tmp[i] != '\0' && tmp[i] != quote)
				freer[j++] = tmp[i++];
		}
		i++;
	}
	freer[j] = '\0';
	free(*str);
	*str = freer;
}

static char	*word_dup(const char *str, int start, int finish, char **split)
{
	char	*word;
	int		i;

	i = 0;
	if (start >= finish)
		return (NULL);
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		array_free(split);
		return (NULL);
	}
	while (start < finish)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**wordsplit(t_msh *mini, char const *s, bool delquotes)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	char	quote;

	if (!s)
		return (0);
	split = malloc((count_words(s) + 1) * sizeof(char *));
	if (!split)
		errexit(mini, "msh: malloc error\n");
	i = 0;
	j = 0;
	index = -1;
	quote = '\0';
	while (i <= ft_strlen(s))
	{
		if (quote && s[i] == quote)
			quote = '\0';
		else if (isquote(s[i]) && quote  == '\0')
		{
			if (index == -1)
				index = i;
			quote = s[i];
		}
		else if ((s[i] != ' ' && s[i] != '\t') && index < 0 && !quote)
			index = i;
		else if (((s[i] == ' ' || s[i] == '\t') || i == ft_strlen(s)) 
				&& index >= 0 && !quote)
		{
			split[j] = word_dup(s, index, i, split);
			if (!split[j])
				errexit(mini, "msh: malloc error\n");
			if (delquotes)
				removequotes(&split[j]);
			index = -1;
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
