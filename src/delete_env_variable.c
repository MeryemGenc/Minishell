/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:15 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:20:57 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	clear_env_variable(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
	env = NULL;
}

void	delete_env_variable(t_shell *g_shell, char *variable_name)
{
	t_env	*temp_env;
	t_env	*prev_env;

	temp_env = g_shell->env;
	prev_env = NULL;
	if (temp_env == NULL)
		return ;
	if (ft_strncmp(temp_env->name, variable_name,
			ft_strlen(variable_name) + 1) == 0)
	{
		g_shell->env = g_shell->env->next;
		clear_env_variable(temp_env);
		return ;
	}
	while (temp_env != NULL && ft_strcmp(temp_env->name, variable_name) != 0)
	{
		prev_env = temp_env;
		temp_env = temp_env->next;
	}
	if (temp_env == NULL)
		return ;
	prev_env->next = temp_env->next;
	clear_env_variable(temp_env);
}
