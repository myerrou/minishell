/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_envirement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:56:53 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/24 08:16:03 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	error_return(char c)
{
	if (c == '-' || c == '/')
		return (-1);
	if (c == '*' || c == '.' || c == ',')
		return (-1);
	if (c == ':' || c == '?' || c == '@')
		return (-1);
	if (c == '[' || c == ']' || c == '^')
		return (-1);
	if (c == '{' || c == '}' || c == '~')
		return (-1);
	if (c == '%' || c == '#')
		return (-1);
	return (0);
}

int	valid_envirement(const char *env)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '+' && env[i] != '=')
	{
		if (error_return(env[i]) == -1)
			return (-1);
		if (env[i] == '_' || env[i] != '_')
			i++;
	}
	if (env[i] == '+' && env[i + 1] != '=')
		return (-1);
	if (env[i] == '+' && env[i + 1] == '=')
		return (5);
	if (env[i] == '=')
	{
		if (!env[i + 1])
			return (2);
		return (2);
	}
	return (1);
}

int	content_len(const char *env)
{
	size_t	i;
	size_t	size_name;

	size_name = 0;
	i = 0;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*envirement_content(char *env)
{
	size_t	j;
	size_t	size_alloc;
	size_t	i;
	char	*envirement_content;

	size_alloc = ft_strlen(env) + 1;
	envirement_content = ft_malloc(sizeof(char) * size_alloc);
	if (!envirement_content)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
		envirement_content[j++] = env[i++];
	envirement_content[j] = '\0';
	return (envirement_content);
}

char	*get_token_content(char *target, t_env *env)
{
	char	*env_val;

	if (!target)
		return (NULL);
	env_val = NULL;
	while (env && env->value)
	{
		if (ft_strcmp(target, env->name) == 0)
		{
			env_val = envirement_content(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
