/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:34 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 10:13:19 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_it_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

void	reset_file(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	execute_the_builtin(t_node *parsed, t_env *env)
{
	if (redirecting(parsed, env))
		return (g_sig.exit_status = 1, 1);
	if (ft_strcmp(parsed->cmd[0], "cd") == 0)
		g_sig.exit_status = ft_cd(parsed->cmd, env);
	if (ft_strcmp(parsed->cmd[0], "echo") == 0)
		g_sig.exit_status = ft_echo(parsed->cmd);
	if (ft_strcmp(parsed->cmd[0], "pwd") == 0)
		g_sig.exit_status = ft_pwd();
	if (ft_strcmp(parsed->cmd[0], "env") == 0)
		g_sig.exit_status = ft_env(env);
	if (ft_strcmp(parsed->cmd[0], "unset") == 0)
		g_sig.exit_status = ft_unset(parsed->cmd, &env);
	if (ft_strcmp(parsed->cmd[0], "export") == 0)
		g_sig.exit_status = ft_export(parsed->cmd, env);
	if (ft_strcmp(parsed->cmd[0], "exit") == 0)
		ft_exit(parsed->cmd);
	reset_file();
	return (g_sig.exit_status);
}
