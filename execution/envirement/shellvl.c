/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:04 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/17 01:10:41 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	lvl_not_valid(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	get_lvl(const char *str)
{
	int		i;
	size_t	sign;
	size_t	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skipallspace(str, &i);
	if (lvl_not_valid(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	increment_shell_level(t_env *env)
{
	size_t	shell_level;
	char	env_name[BUFF_SIZE];
	char	*shlvl;
	char	*shell_level_content;

	shlvl = ft_strdup("");
	shell_level_content = get_token_content("SHLVL", env);
	if (!shell_level_content || ft_strcmp(shell_level_content, "") == 0)
		return ;
	shell_level = get_lvl(shell_level_content) + 1;
	while (env && env->next)
	{
		get_token_name(env_name, env->name);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			shlvl = ft_itoa(shell_level);
			env->value = shlvl;
			return ;
		}
		env = env->next;
	}
}
