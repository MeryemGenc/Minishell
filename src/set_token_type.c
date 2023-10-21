/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:30 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:34:32 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_command(t_token *token)
{
	if (token->quote_check == 1)
		token->type = COMMAND_TYPE;
	else if (is_builtin(token->value))
		token->type = BUILTIN_TYPE;
	else if (is_redirect(token->value))
		token->type = REDIRECT_TYPE;
	else if (is_pipe(token->value))
		token->type = PIPE_TYPE;
	else
		token->type = COMMAND_TYPE;
}

static void	multiple_command_helper(t_shell *g_shell, t_token *token)
{
	if (is_builtin(token->value) && !is_redirect(token->next->value))
		token->type = BUILTIN_TYPE;
	else if (is_redirect(token->value))
	{
		token->type = REDIRECT_TYPE;
		if (ft_strncmp(token->value, "<<", 3) == 0)
			g_shell->heredoc_count += 1;
	}
	else if (is_pipe(token->value))
		token->type = PIPE_TYPE;
	else
		token->type = COMMAND_TYPE;
}

static void	multiple_command(t_shell *g_shell, t_token *token)
{
	while (token != NULL && token->next != NULL)
	{
		multiple_command_helper(g_shell, token);
		if (token->quote_check == 1)
			token->type = COMMAND_TYPE;
		else if (is_redirect(token->value) && !is_operator(token->next->value))
		{
			token->next->type = FILE_TYPE;
			token = token->next;
		}
		token = token->next;
	}
	if (token != NULL)
		single_command(token);
}

void	set_token_type(t_shell *g_shell, t_token *token)
{
	if (token == NULL)
		return ;
	if (token->next == NULL)
		single_command(token);
	else
		multiple_command(g_shell, token);
}
