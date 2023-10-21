/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:06:12 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:29:13 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

static char	*ft_array(char *str, unsigned int count, long int val)
{
	while (count > 0)
	{
		str[val--] = '0' + (count % 10);
		count = count / 10;
	}
	return (str);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		val;
	unsigned int	count;
	int				sign;

	sign = 1;
	val = ft_len(n);
	str = (char *)malloc(sizeof(char) * (val + 1));
	if (!str)
		return (NULL);
	str[val--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		count = n * -1;
		str[0] = '-';
	}
	else
		count = n;
	str = ft_array(str, count, val);
	return (str);
}
