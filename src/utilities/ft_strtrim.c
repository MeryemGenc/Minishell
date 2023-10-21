/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:07:54 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:04:57 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size = ft_strlen(s1);
	while (ft_strchr(set, s1[size]) && size != 0)
		size--;
	return (ft_substr(s1, 0, size + 1));
}

char	*ft_strtrim_char(char const *s1, char c)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] == c)
		start++;
	while (s1[end] == c && end > start)
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
