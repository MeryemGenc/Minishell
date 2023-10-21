/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_separator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:08:20 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 13:20:41 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	*only_word(char *command)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(word_len(command) + 1);
	if (!word)
		return (NULL);
	while (*command != '\0' && !ft_strchr("|<> \"\'", *command))
	{
		word[i] = *command;
		i++;
		command++;
	}
	word[i] = '\0';
	return (word);
}

static char	*only_quoted_words(char *command)
{
	char	*word;
	char	quote;
	int		index;

	word = malloc(word_len(command) + 1);
	if (!word)
		return (NULL);
	index = 0;
	quote = *command;
	word[index] = quote;
	index++;
	command++;
	while (*command != '\0' && *command != quote)
	{
		word[index] = *command;
		index++;
		command++;
	}
	word[index] = *command;
	word[index + 1] = '\0';
	return (word);
}

static char	*only_pipe_redirection(char *command)
{
	char	*word;
	int		i;

	word = malloc(word_len(command) + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (*command != '\0' && ft_strchr("|<>", *command))
	{
		word[i] = *command;
		command++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*command_separator(char *command)
{
	char	*temp_command;

	if (*command != '\0' && !ft_strchr("|<> \"\'", *command))
		temp_command = only_word(command);
	else if (*command != '\0' && ft_strchr("\'\"", *command))
		temp_command = only_quoted_words(command);
	else
		temp_command = only_pipe_redirection(command);
	return (temp_command);
}
