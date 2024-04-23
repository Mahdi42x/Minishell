/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:18:03 by cclaude           #+#    #+#             */
/*   Updated: 2024/04/23 15:39:45 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_token	*current;
	t_token	*token;
	int		index;
	int		start;

	head = NULL;
	current = NULL;
	index = 0;
	start = 0;
	while (line[index] != '\0')
	{
		while (line[index] == ' ')
			index++;
		start = index;
		while (line[index] != ' ' && line[index] != '\0')
			index++;
		if (index > start)
		{
			token = (t_token *)malloc(sizeof(t_token));
			token->str = (char *)malloc((index - start + 1) * sizeof(char));
			memcpy(token->str, &line[start], index - start);
			token->str[index - start] = '\0';
			type_arg(token, 0);
			token->prev = current;
			token->next = NULL;
			if (head == NULL)
				head = token;
			else
				current->next = token;
			current = token;
		}
	}
	return (head);
}
