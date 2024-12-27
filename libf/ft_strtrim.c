/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:35:37 by bjniane           #+#    #+#             */
/*   Updated: 2024/10/25 04:07:59 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	end;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		front = 0;
		end = ft_strlen(s1);
		while (s1[front] && ft_strchr(set, s1[front]))
			front++;
		while (end > front && s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
		str = (char *)ft_malloc(sizeof(char) * (end - front + 1));
		if (str)
		{
			ft_strlcpy(str, &s1[front], end - front + 1);
		}
	}
	return (str);
}

// #include<stdio.h>
// int main() {
//     const char *original = "can you trim this string";
//     const char *set = "cgnia";

//     char *trimmed = ft_strtrim(original, set);
//     printf("Trimmed: %s\n", trimmed);

//     return (0);
// }