/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:06:40 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:32:27 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_strlen_trimmed(char *string, char *set)
{
	int		len;
	char	*trimmed_string;

	if (string == NULL || set == NULL)
		return (0);
	trimmed_string = ft_strtrim(string, set);
	len = ft_strlen(trimmed_string);
	free(trimmed_string);
	return (len);
}

int	ft_strlen_free(char *string)
{
	int	len;

	if (string == NULL)
		return (0);
	len = ft_strlen(string);
	free(string);
	return (len);
}
