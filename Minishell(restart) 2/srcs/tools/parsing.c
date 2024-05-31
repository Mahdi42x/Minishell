/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:26:40 by mawada            #+#    #+#             */
/*   Updated: 2024/04/30 14:32:37 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int		ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '<')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '<'
		&& line[i + 2] && line[i + 2] == '<')
		return (1);
	return (0);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int		is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

int	check_token_syntax(t_minishell *minishell, t_token *token)
{
	if (is_types(token, "TAID") && (!token->next
			|| is_types(token->next, "TAIDPE")))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
		if (token->next)
			ft_putstr_fd(token->next->str, STDERR);
		else
			ft_putstr_fd("newline", STDERR);
		ft_putendl_fd("'", STDERR);
		minishell->ret = 258;
		return (0);
	}
	if (is_types(token, "PE") && (!token->prev
			|| !token->next || is_types(token->prev, "TAIDPE")))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd("'", STDERR);
		minishell->ret = 258;
		return (0);
	}
	return (1);
}

int	check_line(t_minishell *minishell, t_token *token)
{
	while (token)
	{
		if (!check_token_syntax(minishell, token))
			return (0);
		token = token->next;
	}
	return (1);
}



