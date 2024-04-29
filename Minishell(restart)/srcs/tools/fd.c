/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:37:04 by mawada            #+#    #+#             */
/*   Updated: 2024/04/29 12:39:24 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_minishell *minishell)
{
	dup2(minishell->in, STDIN);
	dup2(minishell->out, STDOUT);
}

void	close_fds(t_minishell *minishell)
{
	ft_close(minishell->fdin);
	ft_close(minishell->fdout);
	ft_close(minishell->pipin);
	ft_close(minishell->pipout);
}

void	reset_fds(t_minishell *minishell)
{
	minishell->fdin = -1;
	minishell->fdout = -1;
	minishell->pipin = -1;
	minishell->pipout = -1;
	minishell->pid = -1;
}
