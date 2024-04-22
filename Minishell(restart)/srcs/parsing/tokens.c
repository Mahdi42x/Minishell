/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:18:03 by cclaude           #+#    #+#             */
/*   Updated: 2024/04/22 14:39:49 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
t_token *tokenize(const char *line)
{
	t_token *head = NULL;
	t_token *current = NULL;
	int index = 0;
	int start = 0;

	while (line[index] != '\0')
	{
		// Finden Sie den Anfang eines Tokens
		while (line[index] == ' ') // Überspringen Sie Leerzeichen
			index++;
		start = index;

		// Finden Sie das Ende des Tokens
		while (line[index] != ' ' && line[index] != '\0')
			index++;

		// Erstellen Sie ein neues Token und fügen Sie es zur Liste hinzu
		if (index > start)
		{
			t_token *token = (t_token *)malloc(sizeof(t_token));
			token->str = (char *)malloc((index - start + 1) * sizeof(char));
			memcpy(token->str, &line[start], index - start);
			token->str[index - start] = '\0';
			token->type = CMD;
			token->prev = current;
			token->next = NULL;

			if (head == NULL)
				head = token;
			else
				current->next = token;
			current = token;
		}
	}

	return head;
}