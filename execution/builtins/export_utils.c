/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:15:50 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 09:02:32 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_token_name(var_name, args);
	while (env)
	{
		get_token_name(env_name, env->name);
		if (!ft_strcmp(var_name, env_name))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*get_token_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '+' && src[i] != '='
		&& ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	error_mess(int error, const char *arg)
{
	int	i;

	i = 0;
	if (error == -1)
		ft_putstr_fd(": export: not a valid identifier: ", 2);
	else if (error == 0 || error == -3)
		ft_putstr_fd(": export: not a valid identifier: ", 2);
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

void	ft_add(t_env *new, char *x)
{
	char	*y;

	y = NULL;
	y = ft_strchr(x, '=');
	if (y)
	{
		*y = '\0';
		y++;
		new->name = ft_strdup(x);
		new->value = ft_strdup(y);
	}
	else
	{
		new->name = ft_strdup(x);
		new->value = NULL;
	}
}

int	env_add(char *pair, t_env *env)
{
	t_env	*new;
	char	*x;

	x = pair;
	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (-1);
	ft_add(new, x);
	new->next = NULL;
	while (env && env->next)
		env = env->next;
	env->next = new;
	return (0);
}
