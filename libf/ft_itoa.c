/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:48:24 by bjniane           #+#    #+#             */
/*   Updated: 2024/10/25 04:01:23 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	new;
	int		len;
	char	*tab;

	new = n;
	len = return_len(new);
	tab = (char *)ft_malloc(len + 1);
	if (tab != NULL)
	{
		tab[len--] = '\0';
		if (new == 0)
			tab[0] = 48;
		if (new < 0)
		{
			tab[0] = '-';
			new *= -1;
		}
		while (new)
		{
			tab[len--] = new % 10 + 48;
			new /= 10;
		}
	}
	return (tab);
}
// #include <stdio.h>

// int	main(void) {
// 	int num = -12345;
// 	char *str = ft_itoa(num);

// 	printf("Integer: %d\n", num);
// 	printf("String: %s\n", str);
// 	free(str);
// 	return (0);
// }
