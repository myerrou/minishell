/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:18:11 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/26 11:21:34 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_error(t_token *current)
{
	if (current->type == PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"),
			1);
	else if (current->type == OR)
		return (printf("minishell: syntax error near unexpected token '||'\n"),
			1);
	else if (current->type == SC)
		return (printf("minishell: syntax error near unexpected token\n"), 1);
	return (0);
}

int	word_error(t_token *current)
{
	if (current->type == WORD)
		return (0);
	if (current->type == PIPE || current->type == REDIR_IN
		|| current->type == REDIR_OUT || current->type == HERDOC
		|| current->type == APPEND)
	{
		current = current->next;
		if (current && current->type == WORD)
			return (0);
		else
			return (printf("There is an error here\n"), 1);
	}
	if (current->type == OR || current->type == SC)
		return (printf("We dont support this format\n"), 1);
	return (0);
}

int	syntax_error(t_token *token)
{
	t_token	*current;

	current = token;
	if (!current)
		return (0);
	if (handle_error(current))
		return (1);
	else
	{
		while (current && current->next)
		{
			if (word_error(current))
				return (1);
			current = current->next;
		}
	}
	if (handle_error(current))
		return (1);
	else if (current && (current->type == REDIR_IN || current->type == HERDOC
			|| current->type == REDIR_OUT || current->type == APPEND))
		return (printf("minishell: syntax error near unexpected token\n"), 1);
	return (0);
}
