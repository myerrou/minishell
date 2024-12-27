/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:05:49 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/26 11:21:14 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_files(t_token *current, t_node *node)
{
	t_file	*new_file;
	t_file	*tmp;

	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_file)
		return (1);
	if (process_file(new_file, current->next->content))
		return (1);
	if (current->type == REDIR_IN)
		new_file->redir_in = 1;
	else if (current->type == REDIR_OUT)
		new_file->redir_out = 1;
	else if (current->type == HERDOC)
		new_file->herdoc = 1;
	else if (current->type == APPEND)
		new_file->append = 1;
	if (!node->file)
		node->file = new_file;
	else
	{
		tmp = ft_last(node->file);
		tmp->next = new_file;
	}
	return (0);
}

size_t	size_2d_len(char **str)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		count += j;
		i++;
	}
	return (count);
}

int	compare_character(char c1, char c2)
{
	if (c1 == c2)
		return (0);
	else
		return (1);
}

char	*whitespace_changed(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
		{
			str[i] = ' ';
		}
		i++;
	}
	return (str);
}

void	split_export_var(t_token *current, t_node *node, char **expanded)
{
	char	**splited;

	splited = NULL;
	expanded[0] = whitespace_changed(expanded[0]);
	splited = ft_split(expanded[0], ' ');
	if (current->type == WORD && current->prev == NULL)
		first_cmd(node, splited);
	else if (current->type == WORD && (current->prev->type == WORD
			|| current->prev->type == PIPE))
		other_cmd(node, splited);
}
