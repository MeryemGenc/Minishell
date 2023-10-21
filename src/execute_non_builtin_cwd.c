/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin_cwd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:42:18 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:26:37 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*execute_non_builtin_cwd(char *command)
{
	char	*pwd;
	char	*command_path;

	if (!(*command) || ft_strlen(command) <= 3)
		return (0);
	command++;
	pwd = getcwd(NULL, 0);
	command_path = ft_strjoin(pwd, command);
	free(pwd);
	if (!command_path_is_executable(command_path))
	{
		free(command_path);
		command_path = NULL;
	}
	return (command_path);
}
