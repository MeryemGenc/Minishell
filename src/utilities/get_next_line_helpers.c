/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:07:44 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:05:32 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_has_line_feed(char *line)
{
	while (*line != '\0')
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

char	*ft_create_empty_string(int size)
{
	char	*string;

	string = (char *)malloc(sizeof(char) * size);
	if (string != NULL)
		*string = '\0';
	return (string);
}

char	*ft_add_buffer_to_string(char *string, char *buffer)
{
	char	*new_str;
	int		len;
	int		i;

	if (string == NULL)
		string = ft_create_empty_string(1);
	len = ft_strlen(string) + ft_strlen(buffer);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		new_str[i] = string[i];
		i++;
	}
	while (*buffer != '\0')
	{
		new_str[i] = *buffer;
		i++;
		buffer++;
	}
	new_str[i] = '\0';
	free(string);
	return (new_str);
}
