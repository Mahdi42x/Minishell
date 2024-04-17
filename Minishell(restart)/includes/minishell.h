/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:46 by mawada            #+#    #+#             */
/*   Updated: 2024/04/17 14:27:10 by mawada           ###   ########.fr       */
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
	int				in;
	int				out;
}				t_minishell;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	// pid_t			pid;
}				t_sig;

//parsing
void	parse(t_minishell *minishell);
int		quote_check(t_minishell *minishell, char **line);
int		quotes(char *line, int index);

/*
** SIGNAL
*/
void			sig_int(int code);
void			sig_quit(int code);
void			sig_init(void);

extern t_sig g_sig;
#endif
