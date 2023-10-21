/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:02 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:24:36 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int	is_env_exist(t_shell *g_shell, char *var)
{
	t_env	*env;

	env = g_shell->env;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, var, ft_strlen(var) + 1) == 0)
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	execute_unset(t_shell *g_shell, char **strings)
{
	int		i;
	char	*variable_value;

	i = 1;
	while (strings[i] != NULL)
	{
		variable_value = get_env_value(g_shell, strings[i]);
		if (variable_value != NULL)
		{
			delete_env_variable(g_shell, strings[i]);
			free(variable_value);
		}
		if (is_env_exist(g_shell, strings[i]) && variable_value == NULL)
			delete_env_variable(g_shell, strings[i]);
		i++;
	}
	g_shell->exit_status = 0;
}

void	execute_export(t_shell *g_shell, char **strings)
{
	char	**variable;
	int		i;

	if (strings[1] == NULL)
		print_env_variables_alphabetically(g_shell);
	else
	{
		i = 1;
		while (strings[i] != NULL)
		{
			variable = ft_split(strings[i], '=');
			if (ft_isdigit(variable[0][0]))
			{
				ft_printf(STDERR_FILENO,
					"export: `%s=%s': not a valid identifier\n",
					variable[0], variable[1]);
			}
			else
			{
				add_or_update_env_variable(g_shell, variable[0], variable[1]);
			}
			clear_string_list(variable);
			i++;
		}
	}
}
