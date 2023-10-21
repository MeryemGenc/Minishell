/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:08 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:48:45 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	echo_without_option(t_shell *g_shell, char **strings)
{
	int	i;

	i = 1;
	while (strings[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", strings[i]);
		if (strings[i + 1] != NULL)
			ft_printf(STDOUT_FILENO, "%c", ' ');
		i++;
	}
	ft_printf(STDOUT_FILENO, "%c", '\n');
	g_shell->exit_status = EXIT_SUCCESS;
}

static void	echo_with_option(t_shell *g_shell, char **strings)
{
	int	i;

	i = 2;
	while (strings[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s", strings[i]);
		if (strings[i + 1] != NULL)
			ft_printf(STDOUT_FILENO, "%c", ' ');
		i++;
	}
	g_shell->exit_status = EXIT_SUCCESS;
}

void	execute_echo(t_shell *g_shell, char **strings)
{
	if (strings[1] != NULL && ft_strncmp("-n", strings[1], 3) == 0)
	{
		echo_with_option(g_shell, strings);
	}
	else
	{
		echo_without_option(g_shell, strings);
	}
}
