/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect_and_heredoc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:37 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:10:45 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

static void	writable(t_shell *g_shell, char *file_name, int flag)
{
	int	fd;

	fd = open(file_name, flag, 0744);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_found = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	readable(t_shell *g_shell, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0744);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_found = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	redirect_file_is_wrong(t_token *token)
{
	t_token	*temp_token;

	temp_token = token;
	while (temp_token != NULL)
	{
		if (temp_token->type == REDIRECT_TYPE && temp_token->next == NULL)
		{
			ft_printf(STDERR_FILENO,
				"bash: syntax error near unexpected token `newline\'\n");
			return (1);
		}
		if (temp_token->type == REDIRECT_TYPE && temp_token->next != NULL
			&& temp_token->next->type != FILE_TYPE)
		{
			ft_printf(STDERR_FILENO,
				"bash: syntax error near unexpected token `%s\'\n",
				temp_token->next->value);
			return (1);
		}
		temp_token = temp_token->next;
	}
	return (0);
}

void	execute_redirect_and_heredoc(t_shell *g_shell, t_token *token)
{
	t_token	*temp_token;
	char	*file_name;
	char	*redirect_operator;

	temp_token = token;
	while (temp_token != NULL && temp_token->type != PIPE_TYPE
		&& temp_token->next != NULL)
	{
		if (temp_token->type == REDIRECT_TYPE && temp_token->heredoc_check != 1)
		{
			redirect_operator = temp_token->value;
			file_name = temp_token->next->value;
			if (ft_strncmp(">", redirect_operator, 2) == 0)
				writable(g_shell, file_name, O_WRONLY | O_CREAT | O_TRUNC);
			else if (ft_strncmp("<", redirect_operator, 2) == 0)
				readable(g_shell, file_name);
			else if (ft_strncmp(">>", redirect_operator, 3) == 0)
				writable(g_shell, file_name, O_WRONLY | O_CREAT | O_APPEND);
			else if (ft_strncmp("<<", redirect_operator, 3) == 0)
				execute_heredoc(g_shell, file_name, token);
			temp_token = temp_token->next;
		}
		temp_token = temp_token->next;
	}
}
