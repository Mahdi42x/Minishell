/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:19:39 by mawada            #+#    #+#             */
/*   Updated: 2024/04/15 16:45:42 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_command(char **args)
{
    if (ft_strcmp(args[0], "env") == 0)
    {
        extern char **environ; // Externe Deklaration der Umgebungsvariablen

        // Iteriere über die Umgebungsvariablen und gib sie aus
        int i = 0;
        while (environ[i] != NULL)
        {
            printf("%s\n", environ[i]);
            i++;
        }

       // free_execut_commands(args);
    }
}

