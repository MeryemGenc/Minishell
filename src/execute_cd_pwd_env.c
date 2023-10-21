/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd_pwd_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:10 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:42:08 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	update_old_pwd(t_shell *g_shell, char *old_pwd, char *new_pwd)
{
	t_env	*env;

	env = g_shell->env;
	if (old_pwd == NULL)
	{
		add_or_update_env_variable(g_shell, "OLDPWD", new_pwd);
		return ;
	}
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_pwd);
			return ;
		}
		env = env->next;
	}
}

void	execute_cd(t_shell *g_shell, char **strings)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (strings[1] == NULL)
	{
		update_old_pwd(g_shell, find_in_env_variables(g_shell, "OLDPWD"), pwd);
		chdir(find_in_env_variables(g_shell, "HOME"));
	}
	else if (ft_strncmp("-", strings[1], 2) == 0)
	{
		if (chdir(find_in_env_variables(g_shell, "OLDPWD")) == -1)
			ft_printf(STDERR_FILENO, "%s", "cd: OLDPWD not set\n");
		update_old_pwd(g_shell, find_in_env_variables(g_shell, "OLDPWD"), pwd);
	}
	else
	{
		update_old_pwd(g_shell, find_in_env_variables(g_shell, "OLDPWD"), pwd);
		if (chdir(strings[1]) == -1)
		{
			ft_printf(STDERR_FILENO,
				"cd: %s: No such file or directory\n", strings[1]);
			g_shell->exit_status = 1;
		}
	}
	free(pwd);
}

void	execute_pwd_without_options(t_shell *g_shell)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		perror("Error getcwd failed");
		g_shell->exit_status = 126;
		return ;
	}
	ft_printf(STDOUT_FILENO, "%s\n", current_directory);
	free(current_directory);
	g_shell->exit_status = EXIT_SUCCESS;
}

void	execute_env_without_options(t_shell *g_shell)
{
	t_env	**env_list;
	int		env_count;
	int		i;

	env_count = get_env_variables_count(g_shell);
	if (env_count == 0)
		return ;
	env_list = get_copy_env_list(g_shell, env_count);
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
	g_shell->exit_status = EXIT_SUCCESS;
}
