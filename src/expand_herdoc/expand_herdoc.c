/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:32:45 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/24 13:28:47 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	help_herdoc(char *line, t_var *var)
{
	char	*status;
	int		status_int;

	status_int = g_sig.exit_status;
	if (line[var->i] == '$' && (line[var->i + 1] == '\0'))
	{
		if (!var->result[var->y])
			var->result[var->y] = ft_strdup("");
		var->result[var->y] = append_char(var->result[var->y], line[var->i]);
		if (!var->result[var->y])
			return (1);
		var->i++;
	}
	else if (line[var->i] == '$' && ft_isdigit(line[var->i + 1]))
		var->i += 2;
	else if (line[var->i] == '$' && line[var->i + 1] == '?')
	{
		status = ft_itoa(status_int);
		if (!status)
			return (1);
		var->result[var->y] = status;
		var->i += 2;
	}
	return (0);
}

int	expanssion_herdoc(char *line, t_var *var)
{
	var->start = ++var->i;
	var->str = NULL;
	var->env_value = NULL;
	var->new_res = NULL;
	while (line[var->i] && ft_isalnum(line[var->i]))
		var->i++;
	var->str = ft_substr(line, var->start, var->i - var->start);
	if (!var->str)
		return (1);
	var->env_value = get_token_content(var->str, var->envp);
	if (var->env_value)
		var->new_res = ft_strjoin(var->result[var->y], var->env_value);
	else
		var->new_res = ft_strjoin(var->result[var->y], "");
	if (!var->new_res)
		return (1);
	var->result[var->y] = var->new_res;
	if (!var->result[var->y])
		return (1);
	return (0);
}

int	without_expanssion(char *line, t_var *var)
{
	if (!var->result[var->y])
		var->result[var->y] = ft_strdup("");
	var->result[var->y] = append_char(var->result[var->y], line[var->i]);
	if (!var->result[var->y])
		return (1);
	var->i++;
	return (0);
}

int	handle_expanssion(char *line, t_var *var)
{
	if (line[var->i] == '$' && ((line[var->i + 1] == '\0')
			|| ft_isdigit(line[var->i + 1]) || line[var->i + 1] == '?'))
	{
		if (help_herdoc(line, var))
			return (1);
	}
	else if (line[var->i] == '$' && ft_isalpha(line[var->i + 1]))
	{
		if (expanssion_herdoc(line, var))
			return (1);
	}
	else
	{
		if (without_expanssion(line, var))
			return (1);
	}
	return (0);
}

char	**expand_herdoc(char *line, t_env *envp)
{
	t_var	var;

	var.result = ft_calloc(sizeof(char *), (ft_strlen(line) + 1));
	var.i = 0;
	var.y = 0;
	var.envp = envp;
	if (!var.result)
		return (NULL);
	while (line && line[var.i])
	{
		if (handle_expanssion(line, &var))
			return (NULL);
	}
	if (!var.result[var.y])
		var.result[var.y] = ft_strdup("");
	if (line && line[var.i])
		var.result[++var.y] = NULL;
	return (var.result);
}
