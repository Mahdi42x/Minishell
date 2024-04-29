/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:31:01 by mawada            #+#    #+#             */
/*   Updated: 2024/04/29 13:18:24 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	t_token		token;

	(void)argc;
	(void)argv;
	minishell.in = dup(STDIN);
	minishell.out = dup(STDOUT);
	minishell.exit = 0;
	minishell.ret = 0;
	minishell.no_exec = 0;
	minishell.start = 0;
	reset_fds(&minishell);
	setup_signals();
	env_init(&minishell, envp);
	secret_env_init(&minishell, envp);
	increment_shell_level(minishell.env);
	while (minishell.exit == 0)
	{
		parse(&minishell, &token);
		if (minishell.start != NULL && check_line(&minishell, minishell.start))
			printf("ist hier rein\n");
		free_token(minishell.start);
		minishell.start = NULL;
	}
	free_env(minishell.env);
	free_env(minishell.secret_env);
	return (minishell.ret);
}
