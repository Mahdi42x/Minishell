/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahdi <mahdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:33:42 by mawada            #+#    #+#             */
/*   Updated: 2024/06/03 11:10:24 by mahdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

char	*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	is_in_secret_env(t_env *secret_env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	secret_env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (secret_env)
	{
		get_env_name(secret_env_name, secret_env->value);
		if (ft_strcmp(var_name, secret_env_name) == 0)
		{
			ft_memdel(secret_env->value);
			secret_env->value = ft_strdup(args);
			return (1);
		}
		secret_env = secret_env->next;
	}
	return (0);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	error_ret;

	if (!args[1])
		return (handle_no_args(secret));
	error_ret = handle_errors(args[1]);
	if (error_ret > 0)
		update_env(args[1], env, secret, error_ret);
	return (SUCCESS);
}
