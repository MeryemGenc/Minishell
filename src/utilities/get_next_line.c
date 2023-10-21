/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:07:39 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:06:01 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_fill_string(char *string, int fd)
{
	char	*buffer;
	int		readed_byte;

	buffer = ft_create_empty_string(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	readed_byte = 1;
	while (readed_byte != 0 && ft_has_line_feed(buffer) == 0)
	{
		readed_byte = read(fd, buffer, BUFFER_SIZE);
		if (readed_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed_byte] = '\0';
		string = ft_add_buffer_to_string(string, buffer);
	}
	free(buffer);
	return (string);
}

char	*ft_get_first_line(char *string)
{
	char	*line;
	int		len;

	len = 0;
	while (string[len] != '\0' && string[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (line == NULL)
		return (NULL);
	len = 0;
	while (string[len] != '\0' && string[len] != '\n')
	{
		line[len] = string[len];
		len++;
	}
	if (string[len] == '\n')
	{
		line[len] = string[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_delete_first_line(char *string)
{
	char	*new_str;
	int		line_len;
	int		i;

	line_len = 0;
	while (string[line_len] != '\0' && string[line_len] != '\n')
		line_len++;
	if (string[line_len] == '\0')
	{
		free(string);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(string) - line_len + 1));
	if (new_str == NULL)
		return (NULL);
	line_len++;
	i = 0;
	while (string[line_len] != '\0')
		new_str[i++] = string[line_len++];
	new_str[i] = '\0';
	free(string);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*string[4096];
	char		*line;
	char		*trimmed_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string[fd] = ft_fill_string(string[fd], fd);
	if (string[fd] == NULL)
		return (NULL);
	if (string[fd][0] == '\0')
	{
		free(string[fd]);
		string[fd] = NULL;
		return (NULL);
	}
	line = ft_get_first_line(string[fd]);
	string[fd] = ft_delete_first_line(string[fd]);
	trimmed_line = ft_strtrim_char(line, '\n');
	free(line);
	line = NULL;
	return (trimmed_line);
}
