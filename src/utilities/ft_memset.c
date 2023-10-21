/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:59 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 12:54:00 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	void	*s_address;

	s_address = s;
	while (0 < n)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
		n--;
	}
	return (s_address);
}
