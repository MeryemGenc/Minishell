/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin_commands.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:42 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:58:22 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int	command_path_is_executable(char *command_path)
{
	struct stat	buffer;

	if (stat(command_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

static char	*find_command_path(char *command, char *path_part)
{
	char	*command_path;
	char	*path_part_with_slash;

	command_path = NULL;
	path_part_with_slash = NULL;
	if (ft_strncmp(path_part, command, ft_strlen(path_part)) == 0)
	{
		command_path = ft_strdup(path_part);
	}
	else if (ft_strncmp(command, "/", 1) != 0)
	{
		path_part_with_slash = ft_strjoin(path_part, "/");
		command_path = ft_strjoin(path_part_with_slash, command);
		free(path_part_with_slash);
	}
	else
	{
		command_path = ft_strdup(command);
	}
	return (command_path);
}

static char	*get_executable_path(char **commands, char *path_env_value)
{
	char	**paths;
	char	*command_executable_path;
	int		i;

	paths = ft_split(path_env_value, ':');
	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		command_executable_path = find_command_path(commands[0], paths[i]);
		if (command_path_is_executable(command_executable_path))
		{
			break ;
		}
		if (command_executable_path != NULL)
		{
			free(command_executable_path);
			command_executable_path = NULL;
		}
		i++;
	}
	clear_string_list(paths);
	return (command_executable_path);
}

static void	execute_non_builtin_command_helper(t_shell *g_shell,
	char **commands, char *command_path)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, commands, NULL);
		if (pid > 0)
			exit(0);
	}
	waitpid(pid, &result, 0);
	unlink("bin/.heredoc_temp");
	if (WIFEXITED(result))
		g_shell->exit_status = WEXITSTATUS(result);
}

void	execute_non_builtin_commands(t_shell *g_shell, char **commands)
{
	char	*path_env_value;
	char	*command_executable_path;

	path_env_value = get_path_env_value(g_shell);
	if (path_env_value == NULL || path_env_value[0] == '\0')
		return ;
	command_executable_path = get_executable_path(commands, path_env_value);
	free(path_env_value);
	if (command_executable_path == NULL)
	{
		command_executable_path = execute_non_builtin_cwd(commands[0]);
	}
	if (command_executable_path == NULL)
	{
		if (ft_strchr(commands[0], '/') == NULL)
			ft_printf(STDERR_FILENO, "%s: command not found\n", commands[0]);
		else
			ft_printf(STDERR_FILENO,
				"%s: No such file or directory\n", commands[0]);
		g_shell->exit_status = 127;
		return ;
	}
	execute_non_builtin_command_helper(g_shell, commands,
		command_executable_path);
	free(command_executable_path);
}
