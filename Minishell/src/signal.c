/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:54:17 by mawada            #+#    #+#             */
/*   Updated: 2024/04/16 16:57:55 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_sigint(int sig)
{
    // printf("\nCtrl+C wurde gedrückt.\n");
    // Hier kannst du zusätzliche Aktionen einfügen, die du bei Ctrl+C ausführen möchtest	
	// z.B. Prompt erneut anzeigen
	write(1, "\n", 1);
	write(1, "[Minishell ~]$ ", ft_strlen("[Minishell ~]$ "));
	(void)sig;
}