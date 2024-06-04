/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahdi <mahdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:03 by mawada            #+#    #+#             */
/*   Updated: 2024/06/03 15:40:35 by mahdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//SPACE_LINE MACHEN

// char	*space_line(char *line)
// {
// 	char	*new;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new = space_alloc(line);
// 	while (new && line[i])
// 	{
// 		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
// 			new[j++] = (char)(-line[i++]);
// 		else if (quotes(line, i) == 0 && is_sep(line, i))
// 		{
// 			new[j++] = ' ';
// 			new[j++] = line[i++];
// 			if (quotes(line, i) == 0 && line[i] == '>')
// 				new[j++] = line[i++];
// 			else if (quotes(line, i) == 0 && line[i] == '<')
// 				new[j++] = line[i++];
// 			new[j++] = ' ';
// 		}
// 		else
// 			new[j++] = line[i++];
// 	}
// 	new[j] = '\0';
// 	ft_memdel(line);
// 	return (new);
// }
