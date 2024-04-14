/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:30:03 by mawada            #+#    #+#             */
/*   Updated: 2024/04/14 17:32:55 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd_command(char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
	{
		char pwd[1024];
		if (getcwd(pwd, sizeof(pwd)) != NULL)
		{
			printf("%s\n", pwd);
		}
	}
}