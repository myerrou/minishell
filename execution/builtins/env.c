/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:35:00 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 10:58:47 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//error message for cd builtin
void	err_messo(char *args)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->name && env->name[0] && env->value && env->value[0])
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
