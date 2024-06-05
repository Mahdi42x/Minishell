/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:46 by mawada            #+#    #+#             */
/*   Updated: 2024/06/05 16:51:49 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/time.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define DOUBLE_INPUT 8
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_token
{
	char			*str;
	int				type;
	int				doc;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	char			*line;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
	bool			has_running_process;
}				t_minishell;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

void			sigint_handler_parent(int num);
void			sigint_handler_child(int num);
void			sigquit_handler(int num);
void			set_signals_parent(t_minishell *minishell);
void			set_signals_child(t_minishell *minishell);
void			minshell_helper(t_minishell *minishell);
void			next_tokenhelp(int *j, char *c);


/*
** MINISHELL
*/

void			redir(t_minishell *minishell, t_token *token, int type);
void			input(t_minishell *minishell, t_token *token);
int				minipipe(t_minishell *minishell);
char			*expansions(char *arg, t_env *env, int ret);
void			handle_heredoc(t_token *token, int *pipefd);

/*
** EXEC
*/
void			exec_cmd(t_minishell *minishell, t_token *token);
int				exec_bin(char **args, t_env *env, t_minishell *minishell);
int				exec_builtin(char **args, t_minishell *minishell);
int				is_builtin(char	*command);
char			*path_join(const char *s1, const char *s2);
char			*check_dir(char *bin, char *command);
int				count_tokens(t_token *start);
char			**fill_tab(t_token *start, int size);
char			**cmd_tab(t_token *start);


/*
** BUILTINS
*/
int				ft_echo(char **args);
int				ft_cd(char **args, t_env *env);
int				ft_pwd(void);
int				handle_error(int error_ret, char *arg);
void			add_to_env(int error_ret, char *arg, t_env *env, t_env *secret);
int				ft_export(char **args, t_env *env, t_env *secret);
int				handle_no_args(t_env *secret);
int				handle_errors(char *arg);
void			update_env(char *arg, t_env *env, t_env *secret, int error_ret);
int				ft_env(t_env *env);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);
int				ft_unset(char **args, t_minishell *minishell);
void			mini_exit(t_minishell *minishell, char **cmd);

/*
** PARSING
*/
void			parse(t_minishell *minishell, t_token *token);
t_token			*get_tokens(char *line);
void			squish_args(t_minishell *minishell);
int				is_last_valid_arg(t_token *token);
int				quotes(char *line, int index);
void			type_arg(t_token *token, int separator);
int				is_sep(char *line, int i);
int				ignore_sep(char *line, int i);
void			handle_dollar(char *line, char *new, int *i, int *j);
void			handle_separators(char *line, char *new, int *i, int *j);
char			*space_alloc(char *line);
char			*space_line(char *line);
int				quote_check(t_minishell *minishell, char **line);
int				next_alloc(char *line, int *i);

char			*create_spaced_line(char *line);
void			continue_spaced_line(char *line, char *new, int *i, int *j);
void			complete_spaced_line(char *line, char *new, int *i, int *j);

void 			process_escape_char(char *line, int *i, char *token_str, int *j);
void 			process_quotes(char *line, int *i, char *c);
t_token 		*allocate_token(char *line, int *i);

void			handle_token(t_token *token, t_minishell *minishell);
void			reattach_token(t_token *token, t_token *prev, t_minishell *minishell);
void			initialize_shell(t_minishell *minishell, t_token *token);
int				check_exit_conditions(t_minishell *minishell);
void			process_line(t_minishell *minishell);
void			process_tokens(t_minishell *minishell, t_token *token);
/*
** ENV
*/
int				check_line(t_minishell *minishell, t_token *token);
char			*env_to_str(t_env *lst);
int				env_init(t_minishell *minishell, char **env_array);
int				secret_env_init(t_minishell *minishell, char **env_array);
char			*get_env_value(char *arg, t_env *env);
char			*env_value(char *env);
int				env_value_len(const char *env);
int				is_env_char(int c);
int				is_valid_env(const char *env);
void			print_sorted_env(t_env *env);
void			increment_shell_level(t_env *env);
size_t			size_env(t_env *lst);

/*
** FD TOOLS
*/
void			reset_std(t_minishell *minishell);
void			close_fds(t_minishell *minishell);
void			ft_close(int fd);
void			reset_fds(t_minishell *minishell);

/*
** FREE TOOLS
*/
void			free_token(t_token *start);
void			free_env(t_env *env);
void			free_tab(char **tab);

/*
** TOKEN TOOLS
*/
t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
t_token			*next_run(t_token *token, int skip);

/*
** TYPE TOOLS
*/
int				is_type(t_token *token, int type);
int				is_types(t_token *token, char *types);
int				has_type(t_token *token, int type);
int				has_pipe(t_token *token);
t_token			*next_type(t_token *token, int type, int skip);
int				check_token_error(t_minishell *minishell, t_token *token);
/*
** EXPANSIONS
*/
int				ret_size(int ret);
int				get_var_len(const char *arg, int pos, t_env *env, int ret);
int				arg_alloc_len(const char *arg, t_env *env, int ret);
char			*get_var_value(const char *arg, int pos, t_env *env, int ret);

/*
** SIGNAL
*/
void			setup_signals(void);

extern t_sig	g_sig;

#endif
