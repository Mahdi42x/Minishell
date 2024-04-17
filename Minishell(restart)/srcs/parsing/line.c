/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:03 by mawada            #+#    #+#             */
/*   Updated: 2024/04/17 16:12:24 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_check(t_minishell *minishell, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		minishell->ret = 2;
		minishell->start = NULL;
		return (1);
	}
	return (0);
}

void	parse(t_minishell *minishell)
{
	char	*line;
	// t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (minishell->ret)
	ft_putstr_fd("🤬 ", STDERR);
	else
	ft_putstr_fd("😎 ", STDERR);
	ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
	if (mget_next_line(0, &line) == -2 && (minishell->exit = 1))
	 	ft_putendl_fd("exit", STDERR);
	if (g_sig.sigint == 1)
	minishell->ret = g_sig.exit_status;
	if (quote_check(minishell, &line))
		return ;
}