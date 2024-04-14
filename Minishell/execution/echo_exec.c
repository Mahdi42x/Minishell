/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:00:59 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 19:01:21 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_command(char **args)
{
	if (strcmp(args[0], "echo") == 0)
	{
		// Überprüfe, ob die Option -n angegeben ist
		int option_n = 0;
		int i = 1;
		if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
		{
			option_n = 1;
			i++;
		}

		// Starte ab dem ersten Argument, um den eigentlichen Text zu erhalten
		while (args[i] != NULL)
		{
			printf("%s ", args[i]);
			if (args[i + 1] != NULL) // Überprüfe, ob das nächste Argument vorhanden ist
            {
                printf(" ");
            }
			i++;
		}

		if (!option_n)
		{
			printf("\n");
		}
	}
}