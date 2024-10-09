/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:45:11 by dmarijan          #+#    #+#             */
/*   Updated: 2024/04/10 17:06:33 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*cutline(int start, char **buffer, int bufferlen)
{
	char	*temp;
	int		i;
	int		j;

	temp = get_calloc(bufferlen - start + 1, sizeof(char));
	if (!temp)
		return (get_free(&*buffer));
	i = 0;
	j = 0;
	while (buffer[0][i])
	{
		if (i >= start)
		{
			temp[j] = buffer[0][i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	get_free(&*buffer);
	return (temp);
}

char	*copyline(char **buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[0][i] && buffer[0][i] != '\n')
		i++;
	if (buffer[0][i] == '\n')
		i++;
	line = get_calloc(i + 1, sizeof(char));
	if (!line)
		return (get_free(&*buffer));
	i = 0;
	while (buffer[0][i] && buffer[0][i] != '\n')
	{
		line[i] = buffer[0][i];
		i++;
	}
	if (buffer[0][i] == '\n')
	{
		line[i] = buffer[0][i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fillbuffer(int fd, char **buffer)
{
	int		bread;
	char	*temp;

	bread = 1;
	temp = get_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (get_free(&*buffer));
	while (bread > 0 && get_strchr(*buffer, '\n') == -1)
	{
		bread = read(fd, temp, BUFFER_SIZE);
		if (bread == -1)
		{
			free(temp);
			return (get_free(&*buffer));
		}
		temp[bread] = '\0';
		*buffer = get_strjoin(*buffer, temp);
	}
	free(temp);
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = get_calloc(1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	buffer = fillbuffer(fd, &buffer);
	if (!buffer)
		return (get_free(&buffer));
	line = copyline(&buffer);
	if (buffer)
		buffer = cutline(get_strlen(line), &buffer, get_strlen(buffer));
	return (line);
}
/*
int	main()
{
	char	*string;

	string = malloc(4*sizeof(char));
	string = "lmao";
	puts(string);
	string = malloc(2*sizeof(char));
	string = "ABCD(";
	puts(string);
}
*/
