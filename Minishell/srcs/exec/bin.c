/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:50:02 by mawada            #+#    #+#             */
/*   Updated: 2024/06/01 12:18:29 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

void	box_saption(char **env_array, t_minishell *minishell, int ret)
{
	free_tab(env_array);
	free_token(minishell->start);
	exit(ret);
}

int	magic_box(char *path, char **args, t_env *env, t_minishell *minishell)
{
	char	**env_array;
	char	*ptr;
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		ptr = env_to_str(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		box_saption(env_array, minishell, ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

int	exec_bin(char **args, t_env *env, t_minishell *minishell)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (magic_box(args[0], args, env, minishell));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = magic_box(path, args, env, minishell);
	else
		ret = magic_box(args[0], args, env, minishell);
	free_tab(bin);
	ft_memdel(path);
	return (ret);
}
