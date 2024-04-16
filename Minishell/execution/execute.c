/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:02 by mawada            #+#    #+#             */
/*   Updated: 2024/04/16 18:33:45 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(char **args) {
	int command_executed; // Flag-Variable, um zu verfolgen, ob ein Befehl ausgeführt wurde

	command_executed = 0;
	if (!command_executed && strcmp(args[0], "exit") == 0)
	{
		exit_command(args);
		command_executed = 1;
	}
	if (!command_executed && strcmp(args[0], "pwd") == 0)
	{
		printf("\nentered2\n");
		pwd_command(args);
		command_executed = 1;
	}
	if (!command_executed && strcmp(args[0], "cd") == 0)
	{
		cd_command(args);
		command_executed = 1;
	}
	if (!command_executed && strcmp(args[0], "echo") == 0)
	{
		echo_command(args);
		command_executed = 1;
	}
	if (!command_executed && strcmp(args[0], "ls") == 0)
	{
		ls_command(args);
		command_executed = 1;
	}
	if (!command_executed && strcmp(args[0], "env") == 0)
	{
		env_command(args);
		command_executed = 1;
	}
	if (!command_executed)
	{
	printf("%s: command not found\n", args[0]);
	}
}
