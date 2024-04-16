/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:46 by mawada            #+#    #+#             */
/*   Updated: 2024/04/16 15:02:44 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"
#include <readline/readline.h>

typedef struct t_minishell
{
	int output;
}				t_minishell;

//--------------------//
//---	utils	---//
//---	free ---//
void	free_execut_commands(char **args);
//---	parsing	---//
int		echo_parsing(int argc, char **argv, t_minishell *parsing);
//---	execution	---//
void	execute_command(char **args);
void	exit_command(char **args);
void	pwd_command(char **args);
void	cd_command(char **args);
void	echo_command(char **args);
void	ls_command(char **args);
void	env_command(char **args);
//---	signals	---//
void	handle_sigint(int sig);
//---	main	---//
char	*read_input(char *buffer, int buffer_size);

#endif
