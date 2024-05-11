/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:48:33 by mawada            #+#    #+#             */
/*   Updated: 2024/05/11 14:20:20 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	exec_cmd(t_minishell *minishell, t_token *token)
{
	char	**cmd;
	int		i;

	if (minishell->charge == 0)
		return ;
	cmd = cmd_tab(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expansions(cmd[i], minishell->env, minishell->ret);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(minishell, cmd);
	else if (cmd && is_builtin(cmd[0]))
		minishell->ret = exec_builtin(cmd, minishell);
	else if (cmd)
		minishell->ret = exec_bin(cmd, minishell->env, minishell);
	free_tab(cmd);
	ft_close(minishell->pipin);
	ft_close(minishell->pipout);
	minishell->pipin = -1;
	minishell->pipout = -1;
	minishell->charge = 0;
}
