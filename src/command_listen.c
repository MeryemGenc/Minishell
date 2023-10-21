/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_listen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:30 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:01:24 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	clear_console(void)
{
	ft_printf(STDOUT_FILENO, "\033[2J");
	ft_printf(STDOUT_FILENO, "\033[1;1H");
}

static void	clear_helper(char **line, char **command)
{
	free(*line);
	free(*command);
	*line = NULL;
	*command = NULL;
}

static void	get_exit_status_value(t_shell *g_shell)
{
	if ((*g_signal_no) == SIGINT)
		g_shell->exit_status = 130;
	*g_signal_no = 0;
}

static void	command_listen_two(void)
{
	free(g_signal_no);
	exit(EXIT_SUCCESS);
}

void	command_listen(t_shell *g_shell)
{
	char	*line;
	char	*command;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			exit(EXIT_SUCCESS);
		command = ft_strtrim(line, " \t");
		if (*line == '\0' || *command == '\0')
		{
			clear_helper(&line, &command);
			continue ;
		}
		get_exit_status_value(g_shell);
		if (ft_strncmp(command, "exit", 5) == 0
			|| ft_strncmp(command, "exit ", 5) == 0)
			command_listen_two();
		if (ft_strncmp(command, "clear", 6) == 0)
			clear_console();
		else
			command_handler(g_shell, command);
		add_history(command);
		clear_helper(&line, &command);
	}
}
