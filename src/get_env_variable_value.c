/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variable_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:24 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:27:26 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*get_env_value(t_shell *g_shell, char *command)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	var_name = NULL;
	if (command[0] == '?')
		return (ft_itoa(g_shell->exit_status));
	while (!ft_strchr("|<> \"\'$?=", command[i]))
		i++;
	if (i > 0)
		var_name = ft_substr(command, 0, i);
	var_value = find_in_env_variables(g_shell, var_name);
	if (var_name != NULL)
		free(var_name);
	if (var_value == NULL && *(command) == '=')
		return (ft_strdup("$"));
	else if (var_value == NULL && *(command) == '\"' && *(command - 1) == '$')
		return (ft_strdup("$"));
	else if (var_value == NULL && *(command) == '\"' && *(command - 1) == '?')
		return (ft_strdup("?"));
	else if (var_value == NULL && *(command) == ' ' && *(command - 1) == '$')
		return (ft_strdup("$"));
	return (ft_strdup(var_value));
}

static int	next_command(char *command)
{
	int	i;

	i = 0;
	while (!ft_strchr("|<> \"\'$?=", command[i]))
		i++;
	return (i + 1);
}

static int	dollar_len(t_shell *g_shell, char *command)
{
	char	*temp_command;
	int		len;

	temp_command = command;
	len = 0;
	while (*temp_command != '\0')
	{
		if (*temp_command == '$' && ft_strlen_trimmed(temp_command, "\"") > 1)
		{
			temp_command++;
			len += ft_strlen_free(get_env_value(g_shell, temp_command));
			temp_command += next_command(temp_command) - 1;
		}
		else
		{
			len++;
			temp_command++;
		}
	}
	return (len);
}

char	*get_env_variable_value(t_shell *g_shell, char *command)
{
	char	*new_command;
	int		index;

	new_command = ft_calloc(dollar_len(g_shell, command) + 1, sizeof(char));
	index = 0;
	while (*command != '\0')
	{
		if (*command == '$' && ft_strlen_trimmed(command, "\"") > 1)
		{
			index += ft_strlen_free(get_env_value(g_shell, command + 1));
			ft_strcat_free(new_command, get_env_value(g_shell, command + 1));
			if (*(command + 1) == '$' || *(command + 1) == '?')
				command += 2;
			else
				command += next_command(command + 1);
		}
		else
		{
			new_command[index] = *command;
			index++;
			command++;
		}
	}
	return (new_command);
}
