/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:33:01 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/27 23:11:35 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	first_cmd(t_node *node, char **expanded)
{
	int	j;

	j = 0;
	node->cmd = ft_malloc(sizeof(char *) * (size_2d_len(expanded) + 2));
	if (!node->cmd)
		return ;
	while (expanded[j])
	{
		node->cmd[j] = ft_strdup(expanded[j]);
		if (!node->cmd[j])
			return ;
		j++;
	}
	node->cmd[j] = NULL;
}

void	other_cmd(t_node *node, char **expanded)
{
	int		i;
	int		nb_cmd;
	char	**new_cmd;

	i = 0;
	nb_cmd = 0;
	new_cmd = NULL;
	if (node->cmd != NULL)
	{
		while (node->cmd && node->cmd[nb_cmd])
			nb_cmd++;
	}
	new_cmd = ft_malloc(sizeof(char *) * (nb_cmd + 2));
	if (!new_cmd)
		return ;
	while (i < nb_cmd)
	{
		new_cmd[i] = node->cmd[i];
		i++;
	}
	new_cmd[i] = ft_strdup(expanded[0]);
	new_cmd[i + 1] = NULL;
	node->cmd = new_cmd;
}

int	cmds_conditions(t_token *current, t_env *envp, t_node *node)
{
	char	**expanded;

	expanded = NULL;
	expanded = expand(current->content, envp);
	if (!expanded || !expanded[0])
		return (1);
	if ((compare_character(current->content[0], '$') == 0) && g_sig.flag != 1)
		split_export_var(current, node, expanded);
	else
	{
		if (current->type == WORD && current->prev == NULL)
			first_cmd(node, expanded);
		else if (current->type == WORD && (current->prev->type == WORD
				|| current->prev->type == PIPE))
			other_cmd(node, expanded);
	}
	if (current->type == REDIR_IN || current->type == REDIR_OUT
		|| current->type == HERDOC || current->type == APPEND)
	{
		if (handle_files(current, node))
			return (1);
	}
	return (0);
}

t_node	*while_parsing(t_token *current, t_node *node, t_env *envp)
{
	t_node	*first_node;
	int		i;

	first_node = NULL;
	i = 0;
	while (current)
	{
		if (cmds_conditions(current, envp, node))
			return (NULL);
		else if ((current)->type == PIPE)
		{
			node->op = PIPE;
			ft_lstadd_node(&first_node, node);
			node->next = parsing(&((current)->next), envp);
			if (!node->next)
				return (NULL);
			return (first_node);
		}
		if ((current)->type == HERDOC && g_sig.execute != 1)
			ft__herdoc(current, node->file, envp, i++);
		current = (current)->next;
	}
	return (node);
}

t_node	*parsing(t_token **token, t_env *envp)
{
	t_node	*node;
	t_token	*current;

	if (!token || !(*token))
		return (NULL);
	current = *token;
	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	if (count_herdoc(current) > 16)
	{
		free_trash();
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		exit(2);
	}
	current = *token;
	node = while_parsing(current, node, envp);
	return (node);
}
