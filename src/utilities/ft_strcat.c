/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:07:13 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:31:39 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_strcat(char *dst, const char *src)
{
	int	dst_len;

	dst_len = ft_strlen(dst);
	ft_strcpy(dst + dst_len, src);
	return (dst);
}

void	ft_strcat_free(char *dst, char *src)
{
	if (src == NULL)
		return ;
	ft_strcpy(dst + ft_strlen(dst), src);
	free(src);
}
