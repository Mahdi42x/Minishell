/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:51:56 by mawada            #+#    #+#             */
/*   Updated: 2024/05/13 15:58:57 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void handle_heresig(int sig)
{
	(void)sig;
	ft_putstr("Quit (core dumped)");
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigaction_init(struct sigaction *sa)
{
	if (sa != NULL)
	{
		sa->sa_handler = NULL;
		sa->sa_sigaction = NULL;
		sa->sa_mask = (sigset_t){0};
		sa->sa_flags = 0;
		sa->sa_restorer = NULL;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigaction_init(&sa_int);
	sigaction_init(&sa_quit);
	sa_int.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	if (sa_quit.sa_handler)
		sa_quit.sa_handler = SIG_IGN;
	else
		sa_quit.sa_handler = &handle_heresig;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
