/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:17 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/16 14:28:21 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_env_value(t_shell *g_shell)
{
	char	*path_env_value;

	path_env_value = get_env_value(g_shell, "PATH");
	if (path_env_value == NULL)
	{
		g_shell->exit_status = 1;
		ft_printf(2, "No such file or directory\n");
		return (NULL);
	}
	g_shell->exit_status = 0;
	return (path_env_value);
}
