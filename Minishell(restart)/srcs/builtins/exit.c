/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:59:51 by mawada            #+#    #+#             */
/*   Updated: 2024/05/11 14:09:53 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_exit(t_minishell *minishell, char **cmd)
{
	minishell->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	if (cmd[1])
		ft_putendl_fd("❤️", STDERR);
	else
		ft_putendl_fd("💚", STDERR);
	if (cmd[1] && cmd[2])
	{
		minishell->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		minishell->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		minishell->ret = ft_atoi(cmd[1]);
	else
		minishell->ret = 0;
}
