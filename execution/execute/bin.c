/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:27 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 11:03:54 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	error_message(t_env *env, char *path)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL && ft_getenv(env, "PATH")
		&& *ft_getenv(env, "PATH"))
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied\n", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		g_sig.exit_status = 127;
	else
		g_sig.exit_status = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return (g_sig.exit_status);
}
