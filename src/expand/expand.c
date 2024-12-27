/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:07:00 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/26 11:36:25 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	function_quote(char *line, t_var *var)
{
	if (line[var->i] == '\'' && var->doublqt != -1)
		var->singqt *= -1;
	else if (line[var->i] == '\"' && var->singqt != -1)
		var->doublqt *= -1;
}

int	handle_non_dollar(char *line, t_var *var)
{
	if (!var->result[var->y])
		var->result[var->y] = ft_strdup("");
	if (line[var->i] == '\'' && var->doublqt != -1)
	{
		var->i++;
		return (0);
	}
	else if (line[var->i] == '\"' && var->singqt != -1)
	{
		var->i++;
		return (0);
	}
	if (not_expanded(line, var))
		return (1);
	return (0);
}

int	second_expand(char *line, t_var *var)
{
	while (line[var->i])
	{
		function_quote(line, var);
		if (line[var->i] == '$' && var->singqt != -1 && var->singqt != -1
			&& (line[var->i + 1] == '\0' || line[var->i + 1] == '?'
				|| ft_isdigit(line[var->i + 1])))
		{
			if (helper_function(line, var))
				return (1);
		}
		else if (line[var->i] == '$' && (line[var->i + 1] == '\'' || line[var->i
					+ 1] == '\"') && (var->doublqt != -1 && var->singqt != -1))
		{
			if (handle_qt_after(line, var))
				return (1);
		}
		else if (line[var->i] == '$' && var->singqt != -1
			&& ft_isalpha(line[var->i + 1]))
			var_expansion(line, var);
		else if (handle_non_dollar(line, var))
			return (1);
	}
	return (0);
}

char	**expand(char *line, t_env *envp)
{
	t_var	var;

	var.result = ft_calloc(sizeof(char *), (ft_strlen(line) + 1));
	var.envp = envp;
	var.i = 0;
	var.y = 0;
	var.singqt = 1;
	var.doublqt = 1;
	if (!var.result)
		return (NULL);
	if (second_expand(line, &var))
		return (NULL);
	if (ft_strcmp(var.result[var.y], "echo") == 0)
		g_sig.flag = 1;
	var.result[++var.y] = NULL;
	return (var.result);
}
