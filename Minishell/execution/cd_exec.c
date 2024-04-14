/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:58:55 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 17:59:23 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_command(char **args)
{
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			// Kein Zielverzeichnis angegeben, gehe zum Home-Verzeichnis
			char *home = getenv("HOME");
			if (home == NULL)
			{
				printf("cd: HOME environment variable not set\n");
			}
			else
			{
				if (chdir(home) != 0)
				{
					perror("chdir() error");
				}
			}
		}
		else
		{
			if (chdir(args[1]) != 0)
			{
				perror("chdir() error");
			}
		}
	}
}