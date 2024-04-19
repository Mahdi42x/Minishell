/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:29 by emkalkan          #+#    #+#             */
/*   Updated: 2024/04/14 19:28:46 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_parsing(int argc, char **argv, t_minishell *parsing)
{
	parsing->output = 0;
	if (argc >= 1)
	{
		if (ft_strcmp(argv[0], "echo") == 0)
		{
			if (ft_strcmp(argv[1], "-n") == 0)
			{
				parsing->output = -1;
				return (EXIT_SUCCESS);
			}
			parsing->output = 1;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}