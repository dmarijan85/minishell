/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:38:14 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 17:05:21 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str != c)
			str++;
		while (*str == c && c && str)
			str++;
		count++;
	}
	return (count);
}

static char	*malloc_word(const char *str, char c)
{
	char	*word;
	int		count;

	count = 0;
	while (str[count] && str[count] != c)
		count++;
	word = (char *)malloc(sizeof(char) * (count + 1));
	if (word == 0)
		return (0);
	ft_strlcpy(word, str, count + 1);
	return (word);
}

static char	**ft_free(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		i;

	if (!str || !*str)
		return (0);
	while (*str && *str == c)
		str++;
	arr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (arr == 0)
		return (0);
	i = 0;
	while (*str)
	{
		arr[i] = malloc_word(str, c);
		if (arr[i] == NULL)
			return (ft_free(arr));
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

/*
int main () {

   char	**new;

   
   new = ft_split("hello!", ' ');
	printf("%s", new[0]);
	printf("%s", new[1]);
   return(0);
}
*/
