/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:13:45 by mawada            #+#    #+#             */
/*   Updated: 2024/05/13 16:50:13 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir(t_minishell *minishell, t_token *token, int type)
{
	ft_close(minishell->fdout);
	if (type == TRUNC)
		minishell->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		minishell->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (minishell->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		minishell->ret = 1;
		minishell->no_exec = 1;
		return ;
	}
	dup2(minishell->fdout, STDOUT);
}

void	input(t_minishell *minishell, t_token *token)
{
	ft_close(minishell->fdin);
	minishell->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (minishell->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		minishell->ret = 1;
		minishell->no_exec = 1;
		return ;
	}
	dup2(minishell->fdin, STDIN);
}

int		minipipe(t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		minishell->pipin = pipefd[0];
		minishell->pid = -1;
		minishell->parent = 0;
		minishell->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		minishell->pipout = pipefd[1];
		minishell->pid = pid;
		minishell->last = 0;
		return (1);
	}
}
void	handle_heredoc(t_minishell *minishell, t_token *token)
{
	int fd;
	char *input_buffer;
	char *line;

	// Öffnen der Datei im Lesemodus
	input_buffer = NULL;
	fd = open(token->str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		minishell->ret = 1;
		minishell->no_exec = 1;
		return;
	}

	// Einlesen des Inhalts der Datei
	line = get_next_line(fd);
	while (line)
	{
		input_buffer = ft_strjoin(input_buffer, line);
		input_buffer = ft_strjoin(input_buffer, "\n");
		ft_memdel(line);
	}

	// Schließen der Datei
	close(fd);

	// Aktualisieren des Eingabepuffers
	if (input_buffer)
	{
		rl_replace_line(input_buffer, 0);
		rl_on_new_line();
		rl_redisplay();
		ft_memdel(input_buffer);
	}
}
