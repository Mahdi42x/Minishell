/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:18:03 by cclaude           #+#    #+#             */
/*   Updated: 2024/04/20 15:35:51 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *tokenize(const char *line)
{
	t_token	*head;
	t_token	*current;
	char	**tokens;
	int		i;
	int		j;

	head = NULL;
	current = NULL;
	i = 0;
	j = 0;

	tokens = ft_split(line, ' ');
	if (tokens != NULL && tokens[i] != NULL)
	{
		head = (t_token *)malloc(sizeof(t_token));
		head->str = ft_strdup(tokens[i]);
		head->type = CMD;
		head->prev = NULL;
		head->next = NULL;
		current = head;
		i++;
	}
	while(tokens != NULL && tokens[i] != NULL)
	{
		current->next = (t_token *)malloc(sizeof(t_token));
		current->next->str = ft_strdup(tokens[i]);
		current->next->type = CMD;
		current->next->prev = current;
		current->next->next = NULL;
		current = current->next;
		i++;
	}
	if (tokens != NULL)
	{
		while (tokens[j] != NULL)
		{
			ft_memdel(tokens[j]);
			j++;
		}
		ft_memdel(tokens);
	}
	return(head);
}
