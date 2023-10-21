/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgencali <mgencali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:46 by mgencali          #+#    #+#             */
/*   Updated: 2023/10/19 14:11:16 by mgencali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_env
{
	char			*name;
	char			*value;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	int				quote_check;
	int				heredoc_check;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		dup_fd[2];
	int		file_error_found;
	int		heredoc_count;
	int		token_count;
}	t_shell;

typedef enum e_token_types
{
	BUILTIN_TYPE = 1,
	REDIRECT_TYPE = 2,
	FILE_TYPE = 3,
	COMMAND_TYPE = 4,
	PIPE_TYPE = 5,
}	t_token_types;

int	*g_signal_no;

int		ft_isdigit(int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_char(char const *s1, char c);
char	*ft_substr(char const *s, int start, int len);
int		ft_strlen(const char *s);
int		ft_strlen_trimmed(char *command, char *set);
int		ft_strlen_free(char *string);
char	*ft_strcat(char *dst, const char *src);
void	ft_strcat_free(char *dst, char *src);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_print_char(int fd, int c);
int		ft_print_string(int fd, const char *string);
int		ft_print_pointer(int fd, unsigned long number);
int		ft_print_integer(int fd, int number);
int		ft_print_unsigned_integer(int fd, unsigned int number);
int		ft_print_hexadecimal(int fd, unsigned int number, char c);
int		ft_printf(int fd, const char *format, ...);
int		ft_has_line_feed(char *line);
char	*ft_create_empty_string(int size);
char	*ft_add_buffer_to_string(char *string, char *buffer);
char	*ft_fill_string(char *string, int fd);
char	*ft_get_first_line(char *string);
char	*ft_delete_first_line(char *string);
char	*get_next_line(int fd);
void	command_listen(t_shell *g_shell);
void	command_handler(t_shell *g_shell, char *command);
char	**command_parser(char *command);
char	*command_separator(char *command);
int		word_len(char *command);
char	*skip_pipe_redirection(char *str);
char	*skip_quotes(char *str);
int		pipe_redirection_count(char *command);
void	change_all_env_variable_to_value(t_shell *g_shell, char **commands);
char	*get_env_value(t_shell *g_shell, char *command);
char	*get_env_variable_value(t_shell *g_shell, char *command);
char	*find_in_env_variables(t_shell *g_shell, char *variable_name);
void	add_or_update_env_variable(t_shell *g_shell, char *name, char *value);
void	add_env_to_list(t_env **env, t_env *new_env);
void	delete_env_variable(t_shell *g_shell, char *variable_name);
void	print_env_variables_alphabetically(t_shell *g_shell);
char	*get_path_env_value(t_shell *g_shell);
void	fill_token_list(t_shell *g_shell, char **parsed_commands,
			t_token **token_list);
void	set_token_type(t_shell *g_shell, t_token *token);
int		is_builtin(char *command);
int		is_redirect(char *command);
int		is_pipe(char *command);
int		is_operator(char *command);
void	clear_temp_token(char **temp_token, char *line);
void	clear_token_list(t_token **token_list);
void	clear_env_list(t_env **env_list, int env_count);
void	clear_string_list(char **string_list);
int		redirect_file_is_wrong(t_token *token);
int		heredoc_no_problem(t_shell *g_shell, t_token *token, int *pipe_fd);
void	execute_heredoc(t_shell *g_shell, char *file_name, t_token *token);
void	execute_redirect_and_heredoc(t_shell *g_shell, t_token *token);
char	**get_commands_before_pipe(t_token *before_pipe);
void	last_pipe_handler(t_shell *g_shell);
void	create_pipe(t_token *pipe_token, int *old_pipe_input_fd);
void	execute_commands(t_shell *g_shell, t_token *token);
void	execute_non_builtin_commands(t_shell *g_shell, char **commands);
void	execute_echo(t_shell *g_shell, char **strings);
void	execute_cd(t_shell *g_shell, char **strings);
void	execute_pwd_without_options(t_shell *g_shell);
void	execute_env_without_options(t_shell *g_shell);
void	execute_export(t_shell *g_shell, char **strings);
void	execute_unset(t_shell *g_shell, char **strings);
int		command_path_is_executable(char *command_path);
char	*execute_non_builtin_cwd(char *command);
t_env	**get_copy_env_list(t_shell *g_shell, int env_count);
int		get_env_variables_count(t_shell *g_shell);
void	print_error(char *delimiter);
void	heredoc_handler_two(char *delimiter, char **temp_token, char *line);

#endif
