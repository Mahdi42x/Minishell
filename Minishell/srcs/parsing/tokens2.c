/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahdi <mahdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:18:16 by mahdi             #+#    #+#             */
/*   Updated: 2024/06/03 15:19:51 by mahdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reattach_token(t_token *token, t_token *prev, t_minishell *minishell)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev)
		token->next = prev->next;
	else
		token->next = minishell->start;
	if (!prev)
		prev = token;
	prev->next->prev = token;
	if (minishell->start->prev)
	{
		prev->next = prev->next;
		minishell->start = minishell->start->prev;
	}
	else
	{
		prev->next = token;
		minishell->start = minishell->start;
	}
}

void	handle_token(t_token *token, t_minishell *minishell)
{
	t_token	*prev;

	prev = prev_sep(token, NOSKIP);
	if (is_type(token, ARG) && is_types(prev, "TAID"))
	{
		while (is_last_valid_arg(prev) == 0)
			prev = prev->prev;
		reattach_token(token, prev, minishell);
	}
}

t_token	*allocate_token(char *line, int *i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

void	process_quotes(char *line, int *i, char *c)
{
	if (*c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
		*c = line[(*i)++];
	else if (*c != ' ' && line[*i] == *c)
	{
		*c = ' ';
		(*i)++;
	}
}

void	process_escape_char(char *line, int *i, char *token_str, int *j)
{
	if (line[*i] == '\\' && (*i)++)
		token_str[(*j)++] = line[(*i)++];
	else
		token_str[(*j)++] = line[(*i)++];
}
