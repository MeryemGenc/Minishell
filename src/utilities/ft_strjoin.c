/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:06:49 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:32:11 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	char	*string;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	string = (char *)malloc((s1_length + s2_length + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_memcpy(string, s1, s1_length);
	ft_strlcpy(string + s1_length, s2, s2_length + 1);
	return (string);
}
