/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:23:07 by mawada            #+#    #+#             */
/*   Updated: 2024/04/13 16:12:04 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void execute_command(char **args)
{
	// Hier kannst du den Befehl ausführen
	//printf("Executing command: %s\n", args[0]);

	// Beispiel: Wenn der Befehl "exit" ist, beende die Schleife
	if (ft_strcmp(args[0], "exit") == 0)
	{
		printf("Exiting...\n");
		free_execut_commands(args);
		exit(0);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		char pwd[1024];
		if (getcwd(pwd, sizeof(pwd)) != NULL)
		{
			printf("%s\n", pwd);
		}
	}
	else if (strcmp(args[0], "cd") == 0)
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
	else if (strcmp(args[0], "echo") == 0)
	{
		// Starte ab dem zweiten Argument, um den eigentlichen Text zu erhalten
		int i = 1;
		while (args[i] != NULL)
		{
			printf("%s ", args[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		printf("%s: command not found\n", args[0]);
	}
}
