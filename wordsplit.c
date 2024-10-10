/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:09 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/09 16:34:08 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	free_memory(char **split)
{
	free(split); //TODO: Esto no esta bien no???
}

static char	*word_dup(const char *str, int start, int finish, char **split)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		free_memory(split);
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

char	**wordsplit(char const *s)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if ((s[i] != ' ' || s[i] != '\t') && index < 0)
			index = i;
		else if (((s[i] == ' ' || s[i] == '\t') || i == ft_strlen(s)) 
				&& index >= 0)
		{
			split[j++] = word_dup(s, index, i, split);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
