/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:35:46 by bjniane           #+#    #+#             */
/*   Updated: 2023/11/03 11:43:01 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
	{
		write(fd, &c, 1);
	}
}

// #include<stdio.h>
// #include<fcntl.h>
// int main()
// {
// 	int fd = open("test.txt", O_RDWR | O_CREAT,0666);
// 	printf("FILE DESCRIPTOR : %d",fd);
// 	write(fd, "hello world",11);
// 	close(fd);
// }