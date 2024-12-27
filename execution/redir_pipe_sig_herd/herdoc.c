/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:55:31 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 11:01:48 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_name_file(int num_file)
{
	char	*number;

	number = ft_itoa(num_file);
	g_sig.rand = ft_strjoin("/tmp/hd_", number);
	if (access(g_sig.rand, F_OK) == 0)
		unlink(g_sig.rand);
	return (g_sig.rand);
}

int	ft_execute_heredoc(t_token *token, t_file *file, t_env *env, int fd)
{
	char	*line;
	char	**exp_herdoc;

	line = NULL;
	exp_herdoc = NULL;
	process_file(file, token->next->content);
	while (1)
	{
		line = readline("herdoc> ");
		if (line && !file->expand)
		{
			exp_herdoc = expand_herdoc(line, env);
			free(line);
			line = exp_herdoc[0];
		}
		if (!line)
		{
			ft_putendl_fd("minishell: warning: end-of-file (wanted a del)", 2);
			break ;
		}
		if (!ft_strcmp(line, file->file))
			break ;
		ft_putendl_fd(line, fd);
	}
	return (close(fd), 0);
}

int	ft_status(pid_t pid, int status)
{
	signal(SIGINT, ft_handler);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.exit_status = WTERMSIG(status) + 128;
	return (g_sig.exit_status);
}

char	*ft_fork_heredoc(t_token *token, t_file *file, t_env *env, int i)
{
	pid_t	pid;
	int		fd;
	int		status;

	status = 0;
	g_sig.rand = ft_name_file(i);
	if (!g_sig.rand)
		return (NULL);
	fd = open(g_sig.rand, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("problem in fork", 2);
		return (NULL);
	}
	if (pid == 0)
	{
		signal(SIGINT, ft_sigint_handler);
		ft_execute_heredoc(token, file, env, fd);
		free_trash();
		exit(0);
	}
	g_sig.exit_status = ft_status(pid, status);
	return (close(fd), g_sig.rand);
}

char	*ft__herdoc(t_token *token, t_file *file, t_env *env, int i)
{
	if (token->type == HERDOC)
		g_sig.rand = ft_fork_heredoc(token, file, env, i++);
	return (g_sig.rand);
}
