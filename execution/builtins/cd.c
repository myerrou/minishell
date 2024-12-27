/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:56:04 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 10:58:02 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*find_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->name, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value);
			oldpwd = ft_malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			i = 0;
			while (env->value[i])
			{
				oldpwd[i] = env->value[i];
				i++;
			}
			oldpwd[i] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	if (is_in_env(env, "PWD"))
		update_env_value(env, pwd);
	return (0);
}

static int	update_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", ft_getenv(env, "PWD"));
	if (!oldpwd)
		return (1);
	if (is_in_env(env, "OLDPWD"))
		update_env_value(env, oldpwd);
	return (0);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		env_path = find_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = find_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		printf("%s\n", env_path);
		if (!env_path)
			return (1);
	}
	ret = chdir(env_path);
	if (ret == -1)
		err_messo(env_path);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int	cd_ret;

	if (!args[1])
		cd_ret = go_to_path(0, env);
	else if (args[2])
	{
		ft_putendl_fd("minishell : cd: too many arguments", 2);
		return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			err_messo(args[1]);
	}
	update_oldpwd(env);
	update_pwd(env);
	return (cd_ret);
}
