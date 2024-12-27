/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:58:16 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/27 22:54:56 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	test_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	first_child(int *fd, t_env *env, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (node->cmd && is_it_builtin(node->cmd[0]))
			execute_the_builtin(node, env);
		else
			execute_command(env, node);
		free_trash();
		exit(g_sig.exit_status);
	}
	return (pid);
}

int	second_child(int *fd, t_env *env, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (node)
			execution(node, env);
		free_trash();
		exit(g_sig.exit_status);
	}
	return (pid);
}

int	execute_pipe(t_env *env, t_node *node)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		return (ft_putendl_fd("Error in pipe", 2), 1);
	pid1 = first_child(fd, env, node);
	pid2 = second_child(fd, env, node->next);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.exit_status = WTERMSIG(status) + 128;
	return (0);
}

int	count_herdoc(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == HERDOC)
			i++;
		token = token->next;
	}
	return (i);
}
