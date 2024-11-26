/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:09 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/26 14:43:33 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

static char	*word_dup(const char *str, int start, int finish, char **split)
{
	char	*word;
	int		i;

	i = 0;
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

static void	fuckyounorma(int *index, size_t i, char *quote, char const *s)
{
	if (*index == -1)
		*index = i;
	*quote = s[i];
}

static bool	ihatethenorma(char *quote, char const *s, size_t i, int *index)
{
	if (*quote && s[i] == *quote)
	{
		*quote = '\0';
		return (true);
	}
	if (isquote(s[i]) && *quote == '\0')
	{
		fuckyounorma(index, i, quote, s);
		return (true);
	}
	if ((s[i] != ' ' && s[i] != '\t') && *index < 0 && !*quote)
	{
		*index = i;
		return (true);
	}
	return (false);
}

static char	**wsmyhead(t_msh *mini, char const *s, bool delquotes, char **split)
{
	char	quote;
	size_t	i;
	size_t	j;
	int		index;

	quote = '\0';
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (!ihatethenorma(&quote, s, i, &index) && ((s[i] == ' ' || \
			s[i] == '\t') || i == ft_strlen(s)) && index >= 0 && !quote)
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
	return (split);
}

char	**wordsplit(t_msh *mini, char const *s, bool delquotes)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_calloc((count_words(s, 0, 0, 0) + 1), sizeof(char *));
	if (!split)
		errexit(mini, "msh: malloc error\n");
	return (wsmyhead(mini, s, delquotes, split));
}
