/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:03:43 by bjniane           #+#    #+#             */
/*   Updated: 2023/11/03 14:35:41 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	i = 0;
	j = 0;
	if (dest == NULL && size == 0)
		return (ft_strlen(src));
	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	j = d_len;
	if (size == 0 || size <= d_len)
		return (s_len + size);
	while (src[i] && i < size - d_len - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (d_len + s_len);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	dest[] = "bilal";
// 	char	src[] = "hello how are u";

// 	printf("%zu", strlcat(dest, src, 6));
// }
