/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:56:44 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 10:52:52 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static size_t	size_of_env(char *env)
{
	size_t	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	unset_free(t_env **env, t_env *current, t_env *previous, char *arg)
{
	if (ft_strncmp(arg, current->name, size_of_env(current->name)) == 0)
	{
		if (previous)
			previous->next = current->next;
		else
			*env = current->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	t_env	*current;
	t_env	*previous;
	int		i;

	current = *env;
	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
	{
		current = *env;
		previous = NULL;
		while (current)
		{
			unset_free(env, current, previous, args[i]);
			previous = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
