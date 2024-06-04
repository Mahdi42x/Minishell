/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahdi <mahdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:26:40 by mawada            #+#    #+#             */
/*   Updated: 2024/06/03 14:25:29 by mahdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_line(t_minishell *minishell, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAID")
			&& (!token->next || is_types(token->next, "TAIDPE")))
		{
			return (check_token_error(minishell, token));
		}
		if (is_types(token, "PE") && (!token->prev || !token->next
				|| is_types(token->prev, "TAIDPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			minishell->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
