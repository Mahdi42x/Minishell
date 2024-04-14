/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:15:14 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 17:33:35 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_command(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
	{
		printf("exit\n");
		free_execut_commands(args);
		exit(0);
	}
}
