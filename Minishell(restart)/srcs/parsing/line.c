/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:03 by mawada            #+#    #+#             */
/*   Updated: 2024/04/24 17:03:18 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_check(t_minishell *minishell, char **line)
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
	t_token	*token;
	t_token	*current;

	minishell->line = readline("\033[0;36m\033[1mMinishell ▸ \033[0m");
	add_history(minishell->line);
	if (minishell->line == NULL || ft_strcmp(minishell->line, "exit") == 0)
	{
		ft_putendl_fd("exit", STDERR);
		minishell->exit = 1;
		return ;
	}
	if (ft_strcmp(minishell->line, "env") == 0)
		ft_env(minishell->env); //kommt noch woanders hin
	if (quote_check(minishell, &minishell->line))
		return ;
	token = get_tokens(minishell->line);
	current = token;
	while (current != NULL)
	{
		printf("%s (Type: %d)\n", current->str, current->type);
		current = current->next;
	}
	free_token(token);
	ft_memdel(minishell->line);
}
