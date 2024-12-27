/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:34:47 by myerrou           #+#    #+#             */
/*   Updated: 2024/11/28 10:59:14 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	num_of_args(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

int	ft_check_nnn(char *str)
{
	int	i;
	int	x;
	int	z;

	i = 0;
	z = 1;
	if (str[i] && str[i] == '-')
	{
		x = 0;
		i++;
	}
	while (str[i])
	{
		z = 0;
		if (str[i] != 'n' && str[i] != '\0')
		{
			z = 1;
			break ;
		}
		i++;
	}
	if (z == 0 && x == 0)
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	opt;
	int	first_arg;

	i = 1;
	opt = 0;
	while (args[i] && args[i][0] == '-' && ft_check_nnn(args[i]) == 0)
	{
		opt = 1;
		i++;
	}
	first_arg = 1;
	while (args[i])
	{
		if (!first_arg)
			write(1, " ", 1);
		ft_putstr_fd(args[i], 1);
		i++;
		first_arg = 0;
	}
	if (num_of_args(args) == 1 || (i == 1 && opt == 0))
		write(1, "\n", 1);
	else if (opt == 0)
		write(1, "\n", 1);
	return (0);
}
