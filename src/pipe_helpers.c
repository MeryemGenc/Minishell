/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:40 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:28:35 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

static int	get_commands_length(t_token *token)
{
	int	length;

	length = 0;
	while (token != NULL && token->type != PIPE_TYPE)
	{
		if (token->type == COMMAND_TYPE || token->type == BUILTIN_TYPE)
			length++;
		token = token->next;
	}
	return (length);
}

char	**get_commands_before_pipe(t_token *before_pipe)
{
	char	**commands;
	int		index;
	int		length;

	if (before_pipe != NULL && before_pipe->next != NULL
		&& ft_strncmp(before_pipe->value, ">", 2) == 0)
		before_pipe = before_pipe->next->next;
	index = 0;
	length = get_commands_length(before_pipe);
	commands = (char **)malloc(sizeof(char *) * (length + 1));
	if (!commands)
		return (NULL);
	commands[length] = NULL;
	while (before_pipe != NULL && before_pipe->type != PIPE_TYPE)
	{
		if (before_pipe->type == COMMAND_TYPE
			|| before_pipe->type == BUILTIN_TYPE)
		{
			commands[index] = before_pipe->value;
			index++;
		}
		before_pipe = before_pipe->next;
	}
	return (commands);
}

void	last_pipe_handler(t_shell *g_shell)
{
	char	*command;

	if (g_shell->token_count == 1)
	{
		ft_printf(STDERR_FILENO,
			"bash: syntax error near unexpected token `|'\n");
		return ;
	}
	if (g_shell->exit_status == 2)
		return ;
	while (1)
	{
		command = readline("> ");
		if (command == NULL)
			return ;
		if (*command == '\0')
		{
			free(command);
			continue ;
		}
		command_handler(g_shell, command);
		free(command);
		break ;
	}
}

void	create_pipe(t_token *pipe_token, int *old_pipe_input_fd)
{
	int	new_pipe[2];

	dup2(*old_pipe_input_fd, STDIN_FILENO);
	if (pipe_token == NULL)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*old_pipe_input_fd = dup(new_pipe[0]);
	close(new_pipe[0]);
}
