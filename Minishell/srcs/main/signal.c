/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:51:56 by mawada            #+#    #+#             */
/*   Updated: 2024/05/16 13:23:03 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler_parent(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_child(int num)
{
	(void)num;
	write(1, "\n", 1);
}

void	sigquit_handler(int num)
{
	if (num == SIGQUIT)
	{
		ft_putstr("Quit (core dumped)");
		write(1, "\n", 1);
		rl_on_new_line();
	}
}

void	set_signals_parent(t_minishell *minishell)
{
	(void) *minishell;
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(t_minishell *minishell)
{
	(void) *minishell;
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
}
