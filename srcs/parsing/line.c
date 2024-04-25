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
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
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

void	parse(t_minishell *minishell)
{
	t_token	*token;
	t_token	*current; //nur fuer die Ausgabe

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
	minishell->line = space_line(minishell->line);
	if (minishell->line && minishell->line[0] == '$')
		minishell->line[0] = (char)(-minishell->line[0]);
	minishell->start = get_tokens(minishell->line);
	ft_memdel(minishell->line);
	squish_args(minishell);
	token = minishell->start;
	current = token;
	while (current != NULL)
	{
		printf("%s (Type: %d)\n", current->str, current->type);
		current = current->next;
	}
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
	free_token(token);
}
