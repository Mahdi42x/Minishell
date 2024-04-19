/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:46 by mawada            #+#    #+#             */
/*   Updated: 2024/04/19 18:08:13 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/time.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_token
{
	char			*str;
	int				type;
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
	int				exit;
	int				ret;
	int				no_exec;
	int				in;
	int				out;
	char			*line;
}				t_minishell;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	int				pid;
}				t_sig;

/*
** MINISHELL
*/
void			redir(t_minishell *minishell, t_token *token, int type);
void			input(t_minishell *minishell, t_token *token);
int				minipipe(t_minishell *minishell);
char			*expansions(char *arg, t_env *env, int ret);

/*
** EXEC
*/
void			exec_cmd(t_minishell *minishell, t_token *token);
int				exec_bin(char **args, t_env *env, t_minishell *minishell);
int				exec_builtin(char **args, t_minishell *minishell);
int				is_builtin(char	*command);

/*
** BUILTINS
*/
int				ft_echo(char **args);
int				ft_cd(char **args, t_env *env);
int				ft_pwd(void);
int				ft_export(char **args, t_env *env, t_env *secret);
int				ft_env(t_env *env);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);
int				ft_unset(char **args, t_minishell *minishell);
void			mini_exit(t_minishell *minishell, char **cmd);

/*
** PARSING
*/
void			parse(t_minishell *minishell);
int				quotes(char *line, int index);
t_token			*tokenize(const char *line);


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


/*
** TYPE TOOLS
*/
int				is_type(t_token *token, int type);
int				is_types(t_token *token, char *types);
int				has_type(t_token *token, int type);
int				has_pipe(t_token *token);
t_token			*next_type(t_token *token, int type, int skip);

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
void	setup_signals(void);

#endif
