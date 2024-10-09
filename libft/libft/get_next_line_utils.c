/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:04:05 by dmarijan          #+#    #+#             */
/*   Updated: 2024/03/26 12:38:18 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_calloc(size_t count, size_t size)
{
	char	*ptr;
	char	*str;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	str = ptr;
	while (count)
	{
		*ptr = '\0';
		ptr++;
		count--;
	}
	return (str);
}

size_t	get_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_strjoin(char *dst, char *src)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!src || !dst)
		return (NULL);
	str = get_calloc(((get_strlen(dst) + get_strlen(src)) + 1), sizeof(char));
	if (!str)
		return (get_free(&dst));
	i = 0;
	j = 0;
	while (dst[i])
	{
		str[i] = dst[i];
		i++;
	}
	while (src[j])
		str[i++] = src[j++];
	str[i] = '\0';
	get_free(&dst);
	if (!str[0])
		return (get_free(&str));
	return (str);
}

int	get_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

int	get_nlines_fd(char *mappath)
{
	int		fd;
	int		length;
	char	*line;

	length = 0;
	fd = open(mappath, O_RDONLY);
	while (fd != -1)
	{
		line = get_next_line(fd);
		if (line)
			length++;
		else
			fd = -1;
		free(line);
	}
	close(fd);
	return (length);
}
