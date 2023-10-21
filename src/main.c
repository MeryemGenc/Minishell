/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:11:06 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:20:21 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	init_global_shell(t_shell *g_shell)
{
	g_signal_no = (int *)malloc(sizeof(int));
	*g_signal_no = 0;
	g_shell->env = NULL;
	g_shell->exit_status = 0;
	g_shell->file_error_found = 0;
	g_shell->heredoc_count = 0;
	g_shell->token_count = 0;
}

static void	init_env_variables(char **envp, t_shell *g_shell)
{
	t_env	*env;

	while (*envp != NULL)
	{
		env = malloc(sizeof(t_env));
		if (!env)
			return ;
		env->name = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		env->value = ft_strdup(getenv(env->name));
		env->flag = 1;
		env->next = NULL;
		add_env_to_list(&g_shell->env, env);
		envp++;
	}
}

static void	sigint_handler(int signal_no)
{
	if (access("bin/.heredoc_temp", F_OK) == 0)
	{
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf(STDIN_FILENO, "> ");
	}
	else
	{
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	*g_signal_no = signal_no;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*g_shell;

	(void)argv;
	if (argc != 1)
	{
		ft_printf(STDERR_FILENO, "Error: too many arguments.\n");
		return (0);
	}
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	if (!g_shell)
		return (0);
	unlink("bin/.heredoc_temp");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_global_shell(g_shell);
	init_env_variables(envp, g_shell);
	command_listen(g_shell);
	free(g_signal_no);
}
