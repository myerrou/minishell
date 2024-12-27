/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:06:38 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/26 10:45:55 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*append_char(char *str, char c)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	len = ft_strlen(str);
	new = ft_malloc(len + 2);
	if (!new)
	{
		printf("Failed\n");
		return (NULL);
	}
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}

int	helper_function(char *line, t_var *var)
{
	char	*status;

	if (line[var->i] == '$' && line[var->i + 1] == '\0')
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
		status = ft_itoa(g_sig.exit_status);
		if (!status)
			return (1);
		var->result[var->y] = ft_strjoin(var->result[var->y], status);
		var->i += 2;
	}
	return (0);
}

int	handle_qt_after(char *line, t_var *var)
{
	char	quote;
	int		start;
	char	*str;
	char	*new_one;

	start = 0;
	quote = line[var->i + 1];
	start = var->i + 2;
	var->i = start;
	while (line[var->i] && line[var->i] != quote)
		(var->i)++;
	(var->i)++;
	str = ft_substr(line, start, var->i - start - 1);
	if (!str)
		return (1);
	if (!var->result[var->y])
		var->result[var->y] = ft_strdup("");
	new_one = ft_strjoin(var->result[var->y], str);
	if (!new_one)
		return (1);
	var->result[var->y] = new_one;
	return (0);
}

int	var_expansion(char *line, t_var *var)
{
	var->start = ++(var->i);
	var->str = NULL;
	var->env_value = NULL;
	var->new_res = NULL;
	while (line[var->i] && ft_isalnum(line[var->i]))
		(var->i)++;
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

int	not_expanded(char *line, t_var *var)
{
	var->result[var->y] = append_char(var->result[var->y], line[var->i]);
	if (!var->result[var->y])
		return (1);
	(var->i)++;
	return (0);
}
