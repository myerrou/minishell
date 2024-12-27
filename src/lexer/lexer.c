/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 05:56:42 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/26 10:17:32 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_special(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	special_char(int c)
{
	return (c == 38 || c == 123 || c == 91 || c == 93 || c == 125 || c == 40
		|| c == 41);
}

void	pipe_redirection(t_token **token, char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
		handle_redirection(token, str, i);
	else if (str[*i] == '|')
		handle_pipe(token, str, i);
}

t_token	*ft_lexer(char *str)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if (special_char(str[i]))
			ft_lstadd_back(&token, ft_lstnew(&str[i], SC));
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			pipe_redirection(&token, str, &i);
		else
		{
			handle_word(&token, str, &i);
			continue ;
		}
		i++;
	}
	if (syntax_error(token))
		return (g_sig.exit_status = 1, NULL);
	return (token);
}
