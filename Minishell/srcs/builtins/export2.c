/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahdi <mahdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:07:41 by mahdi             #+#    #+#             */
/*   Updated: 2024/06/03 11:10:36 by mahdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	handle_no_args(t_env *secret)
{
	print_sorted_env(secret);
	return (SUCCESS);
}

int	handle_errors(char *arg)
{
	int	error_ret;

	error_ret = is_valid_env(arg);
	if (arg[0] == '=')
		error_ret = -3;
	if (error_ret <= 0)
		return (print_error(error_ret, arg));
	return (error_ret);
}

void	update_env(char *arg, t_env *env, t_env *secret, int error_ret)
{
	int	new_env;
	int	new_secret_env;

	new_env = 0;
	new_secret_env = 0;

	if (error_ret == 2)
		new_env = 1;
	else
		new_env = is_in_env(env, arg);

	new_secret_env = is_in_secret_env(secret, arg);

	if (new_env == 0)
	{
		if (error_ret == 1)
			env_add(arg, env);
	}
	if (new_secret_env == 0)
	{
		env_add(arg, secret);
	}
}
