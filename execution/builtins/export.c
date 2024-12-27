/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:56:19 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 10:15:55 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	join_value_env(t_env *env, char *arg)
{
	char	key[BUFF_SIZE];
	char	*value;

	value = NULL;
	if (!arg)
		return ;
	get_token_name(key, arg);
	value = ft_strchr(arg, '+');
	if (value)
		value += 2;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			env->value = ft_strjoin(env->value, value);
			break ;
		}
		env = env->next;
	}
}

void	update_env_value(t_env *env, char *arg)
{
	char	key[BUFF_SIZE];
	char	*value;

	value = NULL;
	if (!arg)
		return ;
	get_token_name(key, arg);
	value = ft_strchr(arg, '=');
	if (value)
		value++;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			env->value = ft_strdup(value);
			break ;
		}
		env = env->next;
	}
}

void	help_export(t_env *env, t_env *exp, char *arg, int error_ret)
{
	int	new_env;

	new_env = 0;
	if (error_ret == 2)
		new_env = 1;
	new_env = is_in_env(env, arg);
	if (new_env == 0)
	{
		if (error_ret >= 1 && error_ret != 5)
			env_add(arg, env);
		env_add(arg, exp);
	}
	if (error_ret == 5)
		new_env = 1;
	if (new_env == 1)
	{
		if (error_ret == 2)
			update_env_value(env, arg);
		else
			join_value_env(env, arg);
	}
}

void	ft_exp_loop(t_env *env, t_env *exp, char **args, bool *bad_key)
{
	int	i;
	int	error_ret;

	i = 1;
	error_ret = 0;
	while (args[i])
	{
		error_ret = valid_envirement(args[i]);
		if (args[i][0] == '=' || args[i][0] == '+')
			error_ret = -3;
		if (error_ret <= 0)
		{
			error_mess(error_ret, args[i]);
			*bad_key = true;
			i++;
			continue ;
		}
		help_export(env, exp, args[i], error_ret);
		i++;
	}
}

int	ft_export(char **args, t_env *env)
{
	t_env	*exp;
	bool	bad_key;

	exp = NULL;
	bad_key = false;
	exp = env_init(exp, env_to_tab(env));
	if (!args[1])
		sort_and_print_env(exp);
	ft_exp_loop(env, exp, args, &bad_key);
	if (bad_key == true)
		return (1);
	return (0);
}
