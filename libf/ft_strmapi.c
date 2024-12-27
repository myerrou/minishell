/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:13:41 by bjniane           #+#    #+#             */
/*   Updated: 2024/10/25 04:07:33 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)ft_malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
// #include<stdio.h>
// char to_uppercase(unsigned int index, char c)
// {
//     if (c >= 'a' && c <= 'z')
//         return (c - ('a' - 'A'));
//     return (c);
// }
// int main()
// {
//     const char *string = "Hello, World!";

//     char *result = ft_strmapi(string, to_uppercase);

//     printf("Original String: %s\n", string);
//     printf("Modified String: %s\n", result);

//     free(result);
// 	return (0);
// }