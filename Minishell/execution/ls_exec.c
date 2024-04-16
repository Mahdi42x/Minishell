/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:34:15 by mawada            #+#    #+#             */
/*   Updated: 2024/04/15 16:17:01 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ls_command(char **args)
{
	// Überprüfen, ob das Argument "ls" ist
	if (strcmp(args[0], "ls") == 0)
	{
		// Öffnen des aktuellen Verzeichnisses
		DIR *dir = opendir(".");
		if (dir == NULL)
		{
			perror("Fehler beim Öffnen des Verzeichnisses");
			return;
		}

		// Durchsuchen des Verzeichnisses und Ausgabe der Dateinamen
		struct dirent *dp;
		int count = 0;
		while ((dp = readdir(dir)) != NULL)
		{
			// Überprüfen, ob es sich um eine versteckte Datei handelt (beginnt mit '.')
			if (dp->d_name[0] != '.') // Versteckte Dateien ignorieren
			{
				printf("%s  ", dp->d_name); // Tabulator zur Trennung der Dateinamen
				count++;
			}
		}

		printf("\n"); // Neue Zeile nach Ausgabe aller Dateinamen

		// Schließen des Verzeichnisses
		closedir(dir);
	}
}