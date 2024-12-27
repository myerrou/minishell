/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:12:02 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 10:08:32 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exit_cases_1(char **cmd)
{
	if (cmd[1] && (cmd[1][0] == '-' || cmd[1][0] == '+') && !ft_strisnum(cmd[1]
			+ 1))
	{
		g_sig.exit_status = 2;
		ft_putendl_fd("minishell: exit: -: numeric argument required", 2);
		free_trash();
		exit(g_sig.exit_status);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		g_sig.exit_status = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": please put numeric argument", 2);
		free_trash();
		exit(g_sig.exit_status);
	}
}

void	exit_cases_2(char **cmd)
{
	if (cmd[1] && !cmd[2] && ft_strisnum(cmd[1]))
	{
		g_sig.exit_status = ft_atoi(cmd[1]);
		free_trash();
		exit(g_sig.exit_status);
	}
	else if (!cmd[1])
	{
		g_sig.exit_status = 0;
		free_trash();
		exit(g_sig.exit_status);
	}
}

void	ft_exit(char **cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd[1] && cmd[2])
	{
		g_sig.exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	exit_cases_1(cmd);
	exit_cases_2(cmd);
}
