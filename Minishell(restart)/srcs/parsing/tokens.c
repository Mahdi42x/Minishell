/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:18:03 by cclaude           #+#    #+#             */
/*   Updated: 2024/04/19 18:10:01 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *tokenize(const char *line)
{
	t_token *token;
	int		i;
	int		j;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		
	}
	return(token);
}
