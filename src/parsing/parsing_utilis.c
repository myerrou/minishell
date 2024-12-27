/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:00:35 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/25 21:18:53 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_file	*ft_last(t_file *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_node(t_node **node, t_node *new_node)
{
	t_node	*last;

	if (!node || !new_node)
		return ;
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	last = *node;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

char	*quote_in_file(t_file *file, char *line, char *new_file, int *i)
{
	char	quote;
	int		start;
	char	*str;
	char	*hold;

	start = 0;
	str = NULL;
	hold = NULL;
	quote = line[*i];
	file->expand = 1;
	start = ++(*i);
	*i = start;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	(*i)++;
	str = ft_substr(line, start, *i - start - 1);
	hold = ft_strjoin(new_file, str);
	new_file = hold;
	return (new_file);
}

char	*func_file(char *line, char *new_file, int *i)
{
	char	tmp[2];
	char	*hold;

	hold = NULL;
	tmp[0] = line[*i];
	tmp[1] = '\0';
	hold = ft_strjoin(new_file, tmp);
	new_file = hold;
	return (new_file);
}

int	process_file(t_file *file, char *line)
{
	char	*new_file;
	int		i;

	i = 0;
	new_file = ft_malloc(1);
	*new_file = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			file->ambiguous = 1;
			new_file = quote_in_file(file, line, new_file, &i);
		}
		else
		{
			new_file = func_file(line, new_file, &i);
			i++;
		}
	}
	file->file = ft_strdup(new_file);
	if (!file->file)
		return (1);
	return (0);
}
