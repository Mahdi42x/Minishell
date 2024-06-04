/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:02:05 by mawada            #+#    #+#             */
/*   Updated: 2024/05/11 14:15:49 by mawada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_minishell *minishell, t_env *env)
{
	if (minishell->env == env && env->next == NULL)
	{
		ft_memdel(minishell->env->value);
		minishell->env->value = NULL;
		minishell->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	unset_env_var(char *var, t_minishell *minishell)
{
	t_env	*env;
	t_env	*tmp;

	env = minishell->env;
	if (ft_strncmp(var, env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			minishell->env = env->next;
		else
			minishell->env = NULL;
		free_node(minishell, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(var, env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(minishell, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	ft_unset(char **a, t_minishell *minishell)
{
	if (!(a[1]))
		return (SUCCESS);
	return (unset_env_var(a[1], minishell));
}
