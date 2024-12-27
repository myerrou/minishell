/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:58:01 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/24 11:50:10 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_execvpe(char *file, char **argv, t_env *env)
{
	int		i;
	char	*path;
	char	**paths;
	char	**envp;

	path = NULL;
	envp = env_to_tab(env);
	if (!envp)
		return (-1);
	paths = paths_split(ft_getenv(env, "PATH"));
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], file);
		execve(path, argv, envp);
	}
	return (-1);
}

char	**paths_split(char *path)
{
	int		i;
	char	**paths;

	if (!path)
		return (NULL);
	i = -1;
	paths = ft_split(path, ':');
	while (paths && paths[++i])
		paths[i] = ft_strjoin(paths[i], "/");
	return (paths);
}

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
