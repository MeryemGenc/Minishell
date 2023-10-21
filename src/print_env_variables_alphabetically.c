/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_variables_alphabetically.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:34 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:33:56 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	get_env_variables_count(t_shell *g_shell)
{
	int		count;
	t_env	*temp_env;

	count = 0;
	temp_env = g_shell->env;
	while (temp_env != NULL)
	{
		count++;
		temp_env = temp_env->next;
	}
	return (count);
}

t_env	**get_copy_env_list(t_shell *g_shell, int env_count)
{
	int		i;
	t_env	**env_list;
	t_env	*temp_env;
	t_env	*copy_env;

	i = 0;
	env_list = (t_env **)malloc(sizeof(t_env *) * (env_count + 1));
	if (!env_list)
		return (NULL);
	temp_env = g_shell->env;
	copy_env = NULL;
	while (temp_env != NULL)
	{
		copy_env = malloc(sizeof(t_env));
		if (!copy_env)
			return (NULL);
		copy_env->name = ft_strdup(temp_env->name);
		copy_env->value = ft_strdup(temp_env->value);
		copy_env->flag = 1;
		copy_env->next = NULL;
		env_list[i++] = copy_env;
		temp_env = temp_env->next;
	}
	env_list[i] = NULL;
	return (env_list);
}

static void	sort_env_list(t_env **env_list, int env_count)
{
	int		len;
	int		i;
	int		j;
	t_env	*temp;

	len = env_count;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env_list[i]->name, env_list[j]->name) > 0)
			{
				temp = env_list[i];
				env_list[i] = env_list[j];
				env_list[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_variables_alphabetically(t_shell *g_shell)
{
	t_env	**env_list;
	int		env_count;
	int		i;

	env_count = get_env_variables_count(g_shell);
	if (env_count == 0)
		return ;
	env_list = get_copy_env_list(g_shell, env_count);
	sort_env_list(env_list, env_count);
	i = 0;
	while (i < env_count)
	{
		if (env_list[i]->value == NULL)
		{
			ft_printf(STDOUT_FILENO, "%s=''\n", env_list[i]->name);
			i++;
			continue ;
		}
		ft_printf(STDOUT_FILENO,
			"%s=\"%s\"\n", env_list[i]->name, env_list[i]->value);
		i++;
	}
	clear_env_list(env_list, env_count);
}
