/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:31:01 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 17:08:16 by mawada           ###   ########.fr       */
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
		found = ft_strchr(buffer, '\n');
		if (found != NULL)
		{
			*found = '\0';
			break;
		}

		if (read(STDIN_FILENO, &c, 1) <= 0)
		{
			buffer[i] = '\0'; // Nullterminierung des Strings
			break;
		}

		buffer[i++] = c;

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
		write(STDOUT_FILENO, "[Minishell ~]$ ", 15);  // Prompt anzeigen

		if (read_input(buffer, BUFFER_SIZE) == NULL)
		{
			// Fehler beim Lesen der Eingabe
			printf("Fehler beim Lesen der Eingabe");
			break;
		}
		// Hier kannst du die eingelesene Eingabe weiterverarbeiten
		// Interpretation der Eingabe
		char **args = ft_split(buffer, ' ');
		if (args != NULL)
		{
			execute_command(args);
			free_execut_commands(args);
		}
	}
	return 0;
}
