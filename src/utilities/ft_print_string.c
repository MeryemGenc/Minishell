/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:12 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 12:54:35 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	ft_print_string(int fd, const char *string)
{
	int	i;

	i = 0;
	if (string == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (*string != '\0')
	{
		ft_print_char(fd, *string);
		string++;
		i++;
	}
	return (i);
}
