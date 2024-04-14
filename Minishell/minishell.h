/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:46 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 19:01:34 by mawada           ###   ########.fr       */
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
# include "libft/libft.h"


//--------------------//
//---	utils	---//
//---	free ---//
void	free_execut_commands(char **args);
//---	parsing	---//
//---	execution	---//
void execute_command(char **args);
void exit_command(char **args);
void pwd_command(char **args);
void cd_command(char **args);
void echo_command(char **args);
//---	main	---//
char *read_input(char *buffer, int buffer_size);

#endif
