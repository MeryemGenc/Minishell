/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:13:25 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:13:46 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	print_error(char *delimiter)
{
	char	*txt;

	txt = "here-document delimited by end-of-file";
	ft_printf(STDERR_FILENO,
		"\nbash: warning: %s (wanted `%s')\n", txt, delimiter);
}

static void	heredoc_handler_helper(t_shell *g_shell, int fd,
	char **temp_token, char *line)
{
	change_all_env_variable_to_value(g_shell, temp_token);
	ft_printf(fd, "%s\n", temp_token[0]);
	clear_temp_token(temp_token, line);
}

static void	readable_for_heredoc(char *file_name, t_token *token)
{
	int		fd;
	t_token	*prev_token;

	prev_token = NULL;
	while (token != NULL && token->next != NULL
		&& ft_strncmp(token->next->value, "<<", 2))
	{
		prev_token = token;
		token = token->next;
	}
	if ((prev_token != NULL && ft_strncmp(prev_token->value, "grep", 5) == 0)
		|| ft_strncmp(token->value, "cat", 4) == 0
		|| ft_strncmp(token->value, "head", 5) == 0
		|| ft_strncmp(token->value, "tail", 5) == 0
		|| ft_strncmp(token->value, "sort", 5) == 0)
	{
		fd = open(file_name, O_RDONLY, 0744);
		if (fd == -1)
		{
			ft_printf(STDERR_FILENO, "File can't opened !\n");
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	heredoc_handler(t_shell *g_shell, char *delimiter, int fd)
{
	char	*line;
	char	**temp_token;

	while (1)
	{
		temp_token = (char **)malloc(sizeof(char *) * 2);
		if (!temp_token)
			return ;
		ft_printf(STDIN_FILENO, "> ");
		line = get_next_line(0);
		temp_token[0] = ft_strdup(line);
		temp_token[1] = NULL;
		if (line == NULL)
		{
			heredoc_handler_two(delimiter, temp_token, line);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			clear_temp_token(temp_token, line);
			break ;
		}
		heredoc_handler_helper(g_shell, fd, temp_token, line);
	}
	close(fd);
}

void	execute_heredoc(t_shell *g_shell, char *file_name, t_token *token)
{
	int	fd;

	g_shell->heredoc_count += 1;
	fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_found = 1;
		return ;
	}
	heredoc_handler(g_shell, file_name, fd);
	readable_for_heredoc(".heredoc_temp", token);
}
