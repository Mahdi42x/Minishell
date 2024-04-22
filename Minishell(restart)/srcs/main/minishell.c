/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:31:01 by mawada            #+#    #+#             */
/*   Updated: 2024/04/22 15:58:35 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sig	g_sig;

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	(void)ac;
	(void)av;
	minishell.in = dup(STDIN);
	minishell.out = dup(STDOUT);
	minishell.exit = 0;
	minishell.ret = 0;
	minishell.no_exec = 0;
	setup_signals();
	env_init(&minishell, envp);
	while (minishell.exit == 0)
	{
		parse(&minishell);
	}
}
