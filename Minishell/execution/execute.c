/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:02 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 19:12:27 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(char **args)
{
	exit_command(args);
	pwd_command(args);
	cd_command(args);
	echo_command(args);
	if(&execute_command == NULL)
	{
		printf("%s: command not found\n", args[0]);
	}
}
