/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:47 by mawada            #+#    #+#             */
/*   Updated: 2024/04/13 15:51:20 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// free the commands
void	free_execut_commands(char **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}