/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:25 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/04 14:08:26 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_counter(char *command)
{
	int	count;
	int	word_flag;

	count = pipe_redirection_count(command);
	word_flag = 0;
	while (*command != '\0')
	{
		if (ft_strchr("\"\'", *command))
		{
			count++;
			command = skip_quotes(command);
			word_flag = 0;
			if (*command == '\0')
				return (count);
		}
		if (word_flag == 0 && !ft_strchr("|<> \"\'", *command))
		{
			count++;
			word_flag = 1;
		}
		else if (word_flag == 1 && ft_strchr("|<> ", *command))
			word_flag = 0;
		command++;
	}
	return (count);
}

char	**command_parser(char *command)
{
	char	**commands;
	int		index;

	commands = (char **)ft_calloc(word_counter(command) + 1, sizeof(char *));
	index = 0;
	while (*command != '\0')
	{
		commands[index] = command_separator(command);
		command = command + ft_strlen(commands[index]);
		while (*command == ' ')
			command++;
		index++;
	}
	commands[index] = NULL;
	return (commands);
}
