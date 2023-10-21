/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:12 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:12:03 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	restore_fd_and_clear_commands(t_shell *g_shell, char **commands)
{
	g_shell->file_error_found = 0;
	dup2(g_shell->dup_fd[0], STDIN_FILENO);
	close(g_shell->dup_fd[0]);
	dup2(g_shell->dup_fd[1], STDOUT_FILENO);
	close(g_shell->dup_fd[1]);
	free(commands);
}

static void	execute_commands_selector(t_shell *g_shell, char **commands)
{
	if (commands == NULL || commands[0] == NULL)
	{
		unlink("bin/.heredoc_temp");
		return ;
	}
	if (ft_strcmp("echo", commands[0]) == 0)
		execute_echo(g_shell, commands);
	else if (ft_strcmp("cd", commands[0]) == 0)
		execute_cd(g_shell, commands);
	else if (ft_strcmp("pwd", commands[0]) == 0 && commands[1] == NULL)
		execute_pwd_without_options(g_shell);
	else if (ft_strcmp("export", commands[0]) == 0)
		execute_export(g_shell, commands);
	else if (ft_strcmp("unset", commands[0]) == 0)
		execute_unset(g_shell, commands);
	else if (ft_strcmp("env", commands[0]) == 0 && commands[1] == NULL)
		execute_env_without_options(g_shell);
	else
		execute_non_builtin_commands(g_shell, commands);
}

static void	execute_with_pipe(t_shell *g_shell, t_token *before_pipe,
	t_token *pipe_token, int *pipe_fd)
{
	char	**commands_before_pipe;

	if (redirect_file_is_wrong(before_pipe))
	{
		g_shell->exit_status = 2;
		return ;
	}
	g_shell->dup_fd[0] = dup(STDIN_FILENO);
	g_shell->dup_fd[1] = dup(STDOUT_FILENO);
	if (heredoc_no_problem(g_shell, before_pipe, pipe_fd))
		create_pipe(pipe_token, pipe_fd);
	execute_redirect_and_heredoc(g_shell, before_pipe);
	commands_before_pipe = get_commands_before_pipe(before_pipe);
	if (g_shell->file_error_found == 0)
		execute_commands_selector(g_shell, commands_before_pipe);
	restore_fd_and_clear_commands(g_shell, commands_before_pipe);
}

void	execute_commands(t_shell *g_shell, t_token *token)
{
	t_token	*temp_token;
	int		pipe_fd;

	g_shell->heredoc_count = 0;
	pipe_fd = 0;
	temp_token = token;
	while (temp_token != NULL)
	{
		if (temp_token->type == PIPE_TYPE)
		{
			execute_with_pipe(g_shell, token, temp_token, &pipe_fd);
			if (temp_token->next == NULL)
			{
				last_pipe_handler(g_shell);
				return ;
			}
			token = temp_token->next;
		}
		temp_token = temp_token->next;
	}
	if (temp_token == NULL)
		execute_with_pipe(g_shell, token, temp_token, &pipe_fd);
	if (pipe_fd != 0)
		close(pipe_fd);
}

void	heredoc_handler_two(char *delimiter, char **temp_token, char *line)
{
	print_error(delimiter);
	clear_temp_token(temp_token, line);
}
