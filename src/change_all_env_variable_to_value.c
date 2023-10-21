/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_all_env_variable_to_value.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:49 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:36:11 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	handle_tilde(t_shell *g_shell, char **command)
{
	char	*value;

	value = get_env_value(g_shell, "HOME");
	free(*command);
	*command = value;
}

static void	handle_tilde_with_slash(t_shell *g_shell, char **command)
{
	char	*home;
	char	*value;

	home = get_env_value(g_shell, "HOME");
	value = ft_strjoin(home, &command[0][1]);
	free(home);
	free(*command);
	*command = value;
}

static int	command_contains_dollar_and_quote(char *command)
{
	if (ft_strchr(command, '$')
		&& (ft_strchr(command, '\"') || ft_strchr(command, '\'')))
	{
		return (1);
	}
	return (0);
}

static void	replace_env_variable_value(t_shell *g_shell, char **command)
{
	char	*temp_command;

	temp_command = get_env_variable_value(g_shell, *command);
	free(*command);
	*command = temp_command;
}

void	change_all_env_variable_to_value(t_shell *g_shell, char **commands)
{
	int		i;

	i = 0;
	while (commands[i] != NULL)
	{
		if (ft_strncmp("~", commands[i], 2) == 0)
		{
			handle_tilde(g_shell, &commands[i]);
		}
		else if (commands[i][0] == '~' && commands[i][1] == '/')
		{
			handle_tilde_with_slash(g_shell, &commands[i]);
		}
		else if (command_contains_dollar_and_quote(commands[i]))
		{
			if (commands[i][0] != '\"')
				return ;
			replace_env_variable_value(g_shell, &commands[i]);
		}
		else if (ft_strchr(commands[i], '$') || ft_strchr(commands[i], '?'))
		{
			replace_env_variable_value(g_shell, &commands[i]);
		}
		i++;
	}
}
