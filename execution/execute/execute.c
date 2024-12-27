/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:56 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/27 22:51:24 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	execute_without_path(t_env *env, t_node *token)
{
	char	**envp;

	envp = env_to_tab(env);
	execve(token->cmd[0], token->cmd, envp);
	if (token->cmd[0])
		error_message(env, token->cmd[0]);
}

void	execute_with_path(t_env *env, t_node *token)
{
	if (token->cmd)
		ft_execvpe(token->cmd[0], token->cmd, env);
	if (token->cmd[0])
		error_message(env, token->cmd[0]);
}

void	exec_cmd_help(t_env *env, t_node *node)
{
	if (!node->cmd)
		return ;
	if (redirecting(node, env))
	{
		free_trash();
		exit(1);
	}
	if (!node->cmd)
	{
		free_trash();
		exit(0);
	}
	if ((node->cmd[0] && ft_strchr(node->cmd[0], '/')) || !ft_getenv(env,
			"PATH") || !*ft_getenv(env, "PATH"))
		execute_without_path(env, node);
	else
		execute_with_path(env, node);
	free_trash();
	exit(g_sig.exit_status);
}

void	execute_command(t_env *env, t_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd_help(env, node);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.exit_status = WTERMSIG(status) + 128;
}

int	execution(t_node *parsed, t_env *env)
{
	if (!parsed)
		return (0);
	if (parsed->op == PIPE)
		execute_pipe(env, parsed);
	else if (parsed->cmd && is_it_builtin(parsed->cmd[0]))
		execute_the_builtin(parsed, env);
	else
		execute_command(env, parsed);
	return (0);
}
