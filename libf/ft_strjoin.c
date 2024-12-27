/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:23 by bjniane           #+#    #+#             */
/*   Updated: 2024/10/25 04:07:11 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cont;
	int		i;
	int		s;
	int		len;

	len = my_strlen(s1) + my_strlen(s2) + 1;
	s = 0;
	i = 0;
	cont = ft_malloc(len);
	if (!cont)
		return (NULL);
	while (s1 && s1[i])
		cont[s++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		cont[s++] = s2[i++];
	cont[s] = '\0';
	return (cont);
}
