/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:16:00 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 09:18:56 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*create_env_string(const char *name, const char *value)
{
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;
	char	*env_string;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	total_len = name_len + value_len + 1 + (value != NULL);
	env_string = ft_malloc(total_len);
	if (!env_string)
		return (NULL);
	ft_memcpy(env_string, name, name_len);
	if (value)
		env_string[name_len] = '=';
	ft_memcpy(env_string + name_len + 1, value, value_len);
	env_string[total_len - 1] = '\0';
	return (env_string);
}

char	**help_to_tab(t_env *env, char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = create_env_string(env->name, env->value);
		if (!array[i])
			return (NULL);
		env = env->next;
		i++;
	}
	array[size] = NULL;
	return (array);
}

char	**env_to_tab(t_env *env)
{
	int		size;
	char	**array;

	size = count_nodes(env);
	array = ft_malloc((size + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	help_to_tab(env, array, size);
	return (array);
}
