/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:31:01 by mawada            #+#    #+#             */
/*   Updated: 2024/05/14 13:09:50 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sig	g_sig;

void redir_and_exec(t_minishell *minishell, t_token *token)
{
    static int heredoc_processed = 0; // Static variable to track if heredoc has been processed
    t_token *prev;
    t_token *next;
    int pipe;

    prev = prev_sep(token, NOSKIP);
    next = next_sep(token, NOSKIP);
    pipe = 0;

    // Check if the current token is a heredoc and it hasn't been processed yet
    if (is_type(prev, DOUBLE_INPUT) && !heredoc_processed)
    {
        handle_heredoc(token);
        heredoc_processed = 1; // Mark the heredoc as processed
        return;
    }

    // Reset the flag if the previous token is not a heredoc
    if (!is_type(prev, DOUBLE_INPUT))
        heredoc_processed = 0;

    // Proceed with redir_and_exec for other token types
    if (is_type(prev, TRUNC))
        redir(minishell, token, TRUNC);
    else if (is_type(prev, APPEND))
        redir(minishell, token, APPEND);
    else if (is_type(prev, INPUT))
        input(minishell, token);
    else if (is_type(prev, PIPE))
        pipe = minipipe(minishell);

    if (next && is_type(next, END) == 0 && pipe != 1)
        redir_and_exec(minishell, next->next);
    if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
        && pipe != 1 && minishell->no_exec == 0)
        exec_cmd(minishell, token);
}




void	minishell_(t_minishell *minishell)
{
	t_token	*token;
	int		status;

	token = next_run(minishell->start, NOSKIP);
	if (is_types(minishell->start, "TAID"))
		token = minishell->start->next;
	while (minishell->exit == 0 && token)
	{
		minishell->charge = 1;
		minishell->parent = 1;
		minishell->last = 1;
		redir_and_exec(minishell, token);
		reset_std(minishell);
		close_fds(minishell);
		reset_fds(minishell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (minishell->last == 0)
			minishell->ret = status;
		if (minishell->parent == 0)
		{
			free_token(minishell->start);
			exit(minishell->ret);
		}
		minishell->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

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
	// setup_signals();
	env_init(&minishell, envp);
	secret_env_init(&minishell, envp);
	increment_shell_level(minishell.env);
	while (minishell.exit == 0)
	{
		parse(&minishell, &token);
		if (minishell.start != NULL && check_line(&minishell, minishell.start))
			minishell_(&minishell);
		free_token(minishell.start);
		minishell.start = NULL;
	}
	free_env(minishell.env);
	free_env(minishell.secret_env);
	return (minishell.ret);
}
