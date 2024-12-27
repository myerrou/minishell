/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:58:21 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 11:07:08 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	free_trash();
	exit(130);
}

void	ft_handler(int sig)
{
	(void)sig;
	g_sig.execute = 1;
}

void	ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 130;
	}
}

int	redir_openfile(t_node *node, t_env *envp)
{
	int		fd;
	char	**ex;

	fd = 0;
	if (compare_character(node->file->file[0], '$') == 0)
	{
		ex = expand(node->file->file, envp);
		if (test_quote(ex[0]) && node->file->ambiguous)
			node->file->file = ex[0];
		else
			return (printf("minishell: %s:ambiguous\n", node->file->file), -1);
	}
	if (node->file->herdoc == 1 && g_sig.exit_status != 130)
		fd = open(g_sig.rand, O_RDONLY, 0644);
	else if (node->file->redir_in == 1)
		fd = open(node->file->file, O_RDONLY);
	else if (node->file->redir_out == 1)
		fd = open(node->file->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->file->append == 1)
		fd = open(node->file->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("minishell"), fd);
	return (fd);
}

int	redirecting(t_node *node, t_env *envp)
{
	int	fd;

	while (node->file)
	{
		fd = redir_openfile(node, envp);
		if (fd == -1)
			return (1);
		if (node->file->herdoc == 1)
			dup2(fd, STDIN_FILENO);
		else if (node->file->redir_in == 1)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		node->file = node->file->next;
	}
	return (0);
}
