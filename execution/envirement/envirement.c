/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:56:59 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/24 08:16:31 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

size_t	size_env(t_env *env)
{
	size_t	env_len;

	env_len = 0;
	while (env && env->next != NULL)
	{
		if (env->value != NULL)
		{
			env_len += ft_strlen(env->name) + ft_strlen(env->value);
			env_len++;
		}
		env = env->next;
	}
	return (env_len);
}

t_env	*lst_env_help(t_env *new, char *x)
{
	char	*y;

	y = NULL;
	y = ft_strchr(x, '=');
	if (y)
	{
		*y = '\0';
		y++;
		new->value = ft_strdup(y);
		if (!new->value)
			return (NULL);
	}
	else
		new->value = NULL;
	return (new);
}

void	ft_lstadd_env(t_env **node, t_env *new_node)
{
	t_env	*last;

	if (!node || !new_node)
		return ;
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	last = *node;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

t_env	*ft_lst_env(char *content)
{
	t_env	*new;
	char	*x;

	x = ft_strdup(content);
	if (!x)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	lst_env_help(new, x);
	new->name = x;
	new->next = NULL;
	return (new);
}

t_env	*env_init(t_env *env, char **env_arr)
{
	size_t	i;

	i = 0;
	while (env_arr && env_arr[i])
	{
		ft_lstadd_env(&env, ft_lst_env(env_arr[i]));
		i++;
	}
	return (env);
}
