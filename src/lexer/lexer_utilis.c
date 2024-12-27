/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:33:32 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/24 13:27:21 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back(t_token **token, t_token *new_token)
{
	t_token	*last;

	if (!token || !new_token)
		return ;
	if (*token == NULL)
	{
		*token = new_token;
		new_token->prev = NULL;
		return ;
	}
	last = ft_lstlast(*token);
	last->next = new_token;
	new_token->prev = last;
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ft_lstnew(char *content, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
		return (NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}
