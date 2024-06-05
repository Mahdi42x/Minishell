/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:03 by mawada            #+#    #+#             */
/*   Updated: 2024/06/05 16:51:31 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialize_shell(t_minishell *minishell, t_token *token)
{
	token->doc = 0;
	set_signals_parent(minishell);
	minishell->line = readline("\033[0;36m\033[1mMinishell ▸ \033[0m");
	set_signals_child(minishell);
	add_history(minishell->line);
}

int	check_exit_conditions(t_minishell *minishell)
{
	if (minishell->line == NULL || ft_strcmp(minishell->line, "exit") == 0)
	{
		ft_putendl_fd("exit", STDERR);
		minishell->exit = 1;
		ft_memdel(minishell->line);
		return (1);
	}
	return (0);
}

void	process_line(t_minishell *minishell)
{
	if (quote_check(minishell, &minishell->line))
		return ;
	minishell->line = space_line(minishell->line);
	if (minishell->line && minishell->line[0] == '$')
		minishell->line[0] = (char)(-minishell->line[0]);
	minishell->start = get_tokens(minishell->line);
	ft_memdel(minishell->line);
	squish_args(minishell);
}

void	process_tokens(t_minishell *minishell, t_token *token)
{
	(void) minishell;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}

void	next_tokenhelp(int *j, char *c)
{
	*j = 0;
	*c = ' ';
}
