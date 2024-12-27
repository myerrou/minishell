/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:04:02 by bjniane           #+#    #+#             */
/*   Updated: 2023/11/03 18:17:55 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	str[30];
	long	nb;

	i = 0;
	if (fd != -1)
	{
		nb = (long)n;
		if (nb < 0)
		{
			write(fd, "-", 1);
			nb = -nb;
		}
		while (nb >= 10)
		{
			str[i++] = '0' + nb % 10;
			nb /= 10;
		}
		str[i] = '0' + nb;
		while (i >= 0)
			write(fd, &str[i--], 1);
	}
}
