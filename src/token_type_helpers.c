/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:24 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/04 14:10:25 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	int		i;
	char	*commands[7];

	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(command, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_redirect(char *command)
{
	int		i;
	char	*commands[4];

	commands[0] = "<";
	commands[1] = ">";
	commands[2] = "<<";
	commands[3] = ">>";
	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(command, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_pipe(char *command)
{
	if (ft_strcmp(command, "|") == 0)
		return (1);
	return (0);
}

int	is_operator(char *command)
{
	if (is_redirect(command) == 1 || is_pipe(command) == 1)
		return (1);
	return (0);
}
