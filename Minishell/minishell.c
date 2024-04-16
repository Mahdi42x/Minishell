/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:31:01 by mawada            #+#    #+#             */
/*   Updated: 2024/04/16 19:06:40 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input(char *buffer, int buffer_size)
{
	int i = 0;
	char *found;
	char c;

	memset(buffer, 0, buffer_size);

	while (1)
	{
		found = strchr(buffer, '\n');
		if (found != NULL)
		{
			*found = '\0';
			break;
		}

		// Signalhandler für SIGINT setzen
		signal(SIGINT, handle_sigint);

		if (read(STDIN_FILENO, &c, 1) <= 0)
		{
			// EOF erkannt
			buffer[i] = '\0';
			return NULL;
		}

		buffer[i++] = c;

		// Überprüfen, ob das Zeilenumbruchzeichen gefunden wurde
	if (c == '\n')
	{
	    buffer[i] = '\0';
	    break;
	}

		if (i >= buffer_size - 1) // Pufferüberlauf vermeiden
			break;
	}

	return buffer;
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char buffer[BUFFER_SIZE];
	while (1)
	{
		write(1, "[Minishell ~]$ ", ft_strlen("[Minishell ~]$ "));  // Prompt anzeigen

		if (read_input(buffer, BUFFER_SIZE) == NULL)
		{
			// Fehler beim Lesen der Eingabe
			printf("\nexit\n");
			break;
		}
		char **args = ft_split(buffer, ' ');
		if (args != NULL)
		{
			execute_command(args);
			free_execut_commands(args);
		}
		
		// Hier kannst du die eingelesene Eingabe weiterverarbeiten
		// Interpretation der Eingabe
	}
	return 0;
}
