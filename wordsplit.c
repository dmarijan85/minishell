/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:09 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/26 18:13:01 by dmarijan         ###   ########.fr       */
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

void	removequotes(char **str)
{
	char	*tmp;
	char	*freer;
	int		i;
	int		j;

	
	i = 0;
	j = 0;
	tmp = *str;
	if (!istherequotes(tmp))
		return ;
	freer = malloc((ft_strlen(*str) - howmanyquotes(*str) + 1) * sizeof(char));
	if (!freer)
		errexit(mini, "msh: malloc error?!");
	while (tmp[i])
	{
		if (!isquote(tmp[i]))
			freer[j++] = tmp[i];
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
		return (NULL);//TODO
	}
	while (start < finish)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	removequotes(&word);
	return (word);
}

char	**wordsplit(char const *s)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	char	quote;

	if (!s)
		return (0);//TODO
	split = malloc((count_words(s) + 1) * sizeof(char *));
	if (!split)
		return (0);//errexit(mini, "msh: malloc error\n");
	i = 0;
	j = 0;
	index = -1;
	quote = '\0';
	while (i <= ft_strlen(s))
	{
		if (quote && s[i] == quote)
			quote = '\0';
		else if (isquote(s[i]))
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
			split[j++] = word_dup(s, index, i, split);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
