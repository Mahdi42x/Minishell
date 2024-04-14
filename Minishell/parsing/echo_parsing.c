/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:29 by emkalkan          #+#    #+#             */
/*   Updated: 2024/04/14 19:05:26 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_parsing(int argc, char **argv, t_parsing *parsing)
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
