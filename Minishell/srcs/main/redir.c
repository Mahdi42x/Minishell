/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:13:45 by mawada            #+#    #+#             */
/*   Updated: 2024/06/07 13:44:49 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir(t_minishell *minishell, t_token *token, int type)
{
	ft_close(minishell->fdout);
	if (type == TRUNC)
		minishell->fdout = open(token->str,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		minishell->fdout = open(token->str,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
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

int	minipipe(t_minishell *minishell)
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

void	pipehelp(int *fd, t_token *token, int *pipefd, int e)
{
	if (e == 0)
	{
		if (pipe(fd) == -1)
		{
			ft_putendl_fd("Pipe creation failed", STDERR);
			return ;
		}
	}
	if (e == 1)
	{
		close(fd[1]);
		close(*pipefd);
		*pipefd = fd[0];
		dup2(*pipefd, STDIN);
		token->doc = 1;
	}
}

void	handle_heredoc(t_token *token, int *pipefd)
{
	char	*line;
	int		fd[2];

	pipehelp(fd, token, pipefd, 0);
	ft_putstr_fd("> ", STDERR);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, token->str, strlen(token->str))
			&& line[ft_strlen(token->str)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("> ", STDERR);
		line = get_next_line(0);
	}
	pipehelp(fd, token, pipefd, 1);
}
