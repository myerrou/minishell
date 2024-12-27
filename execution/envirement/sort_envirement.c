/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envirement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:57:13 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/26 09:07:02 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_swapp(t_env *ptr1)
{
	char	*timp;
	char	*tamp;

	timp = NULL;
	tamp = NULL;
	timp = ptr1->name;
	tamp = ptr1->value;
	ptr1->name = ptr1->next->name;
	ptr1->value = ptr1->next->value;
	ptr1->next->name = timp;
	ptr1->next->value = tamp;
}

void	sort_envirement(t_env *head)
{
	int		swapped;
	t_env	*ptr1;

	swapped = 1;
	if (!head)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != NULL)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				ft_swapp(ptr1);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
	}
}

void	sort_and_print_env(t_env *env)
{
	sort_envirement(env);
	while (env)
	{
		if (env->name)
		{
			ft_putstr_fd("declare -x ", 1);
			printf("%s", env->name);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
}
