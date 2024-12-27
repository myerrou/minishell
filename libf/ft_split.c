/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:47:10 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/24 14:08:05 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static int	fill_string(const char *s, char c, char **ret, size_t len)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			ret[i] = ft_substr(s - len, 0, len);
			if (!ret[i])
				return (1);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = ft_malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	if (fill_string(s, c, ret, 0) != 0)
		return (NULL);
	return (ret);
}

// #include <stdio.h>
// int main() {
//     const char *input = "    hello.world.how.aure .yo...   jkh  jkgj.";
//     char delimiter = '.';
//     char **result = ft_split(input, delimiter);
//     if (result) {
//         for (int i = 0; result[i] != NULL; i++) {
//             printf("Token %d: %s\n", i, result[i]);
//             free(result[i]);
//         }
//         free(result);
//     }
//     return (0);
// }