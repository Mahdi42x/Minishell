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

static void	free_node(t_env **head, t_env *env)
{
	if (*head == env && env->next == NULL)
	{
		ft_memdel((*head)->value);
		(*head)->value = NULL;
		(*head)->next = NULL;
		return;
	}
	if (*head == env)
	{
		*head = env->next;
	}
	else
	{
		t_env *prev = *head;
		while (prev && prev->next != env)
			prev = prev->next;
		if (prev)
			prev->next = env->next;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	unset_env_var(char *var, t_minishell *minishell)
{
	t_env	*env;
	t_env	*tmp;

	// Entfernen aus env-Liste
	env = minishell->env;
	if (env && ft_strncmp(var, env->value, env_size(env->value)) == 0)
	{
		free_node(&minishell->env, env);
	}
	else
	{
		while (env && env->next)
		{
			if (ft_strncmp(var, env->next->value, env_size(env->next->value)) == 0)
			{
				tmp = env->next->next;
				free_node(&minishell->env, env->next);
				env->next = tmp;
				break;
			}
			env = env->next;
		}
	}

	// Entfernen aus secret_env-Liste
	env = minishell->secret_env;
	if (env && ft_strncmp(var, env->value, env_size(env->value)) == 0)
	{
		free_node(&minishell->secret_env, env);
	}
	else
	{
		while (env && env->next)
		{
			if (ft_strncmp(var, env->next->value, env_size(env->next->value)) == 0)
			{
				tmp = env->next->next;
				free_node(&minishell->secret_env, env->next);
				env->next = tmp;
				break;
			}
			env = env->next;
		}
	}

	return (SUCCESS);
}

int	ft_unset(char **a, t_minishell *minishell)
{
	if (!(a[1]))
		return (SUCCESS);
	return (unset_env_var(a[1], minishell));
}
