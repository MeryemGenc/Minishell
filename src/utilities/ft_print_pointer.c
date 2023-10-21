/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:22 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/04 14:05:23 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_pointer_hex_len(unsigned long number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number = number / 16;
		len++;
	}
	return (len);
}

static int	ft_print_pointer_hex(int fd, unsigned long number)
{
	int	len;

	len = ft_pointer_hex_len(number);
	if (number <= 9)
		ft_print_char(fd, number + '0');
	else if (number < 16)
		ft_print_char(fd, (number - 10) + 'a');
	else
	{
		ft_print_pointer_hex(fd, number / 16);
		ft_print_pointer_hex(fd, number % 16);
	}
	return (len);
}

int	ft_print_pointer(int fd, unsigned long number)
{
	int	len;

	len = ft_print_string(fd, "0x");
	len += ft_print_pointer_hex(fd, number);
	return (len);
}
