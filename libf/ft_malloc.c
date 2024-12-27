/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 03:44:13 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/23 22:12:35 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "libft.h"

void	ft_lstadd_list(t_list **list, t_list *new_node)
{
	t_list	*last;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

t_list	*ft_new_list(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Failed allocation\n");
		exit(1);
	}
	ft_lstadd_list(&g_sig.trash, ft_new_list(ptr));
	return (ptr);
}

void	free_trash(void)
{
	ft_lstclear(&g_sig.trash, free);
}
