/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:03 by mawada            #+#    #+#             */
/*   Updated: 2024/06/05 16:49:38 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

static char	*spaceinit(char *line, int *i, int *j)
{
	*i = 0;
	*j = 0;
	return (space_alloc(line));
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	new = spaceinit(line, &i, &j);
	while (line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

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

void	parse(t_minishell *minishell, t_token *token)
{
	int	quit_printed;

	quit_printed = 0;
	initialize_shell(minishell, token);
	if (check_exit_conditions(minishell))
		return ;
	process_line(minishell);
	token = minishell->start;
	process_tokens(minishell, token);
	if (quit_printed == 0 && signal(SIGQUIT, sigquit_handler) != SIG_ERR)
		quit_printed = 1;
}
